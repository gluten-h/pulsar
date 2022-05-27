
#include "gamma_correction.hlsli"


TextureCube mat_albedo_map : register(t0);
TextureCube mat_exposure_map : register(t1);

SamplerState smpl : register(s0);

cbuffer skybox_cb : register(b0)
{
	float3 mat_albedo_color;
	bool mat_albedo_srgb;
	
	float mat_exposure;
	float3 pd0;
}

cbuffer camera_cb : register(b1)
{
	float3 cam_pos;
	float cam_gamma;
	
	float3 cam_dir;
	float cam_exposure;
};


float4	frag(float4 pos : SV_POSITION, float3 world_pos : POSITION) : SV_TARGET
{
	float3 albedo_map = mat_albedo_map.Sample(smpl, world_pos).xyz;
	float exposure = mat_exposure_map.Sample(smpl, world_pos).x * mat_exposure;
	float4 color = float4(lerp(albedo_map, srgb_to_linear(albedo_map, cam_gamma), mat_albedo_srgb) * mat_albedo_color, exposure);

	return (color);
}