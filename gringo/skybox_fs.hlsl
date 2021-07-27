
#include "gamma_correction.hlsli"


cbuffer skybox_cb : register(b0)
{
	float3	skybox_color;
	bool	skybox_srgb;
	
	float	cam_gamma;
	float	skybox_exposure;
	float2	pd0;
}


TextureCube mat_env_map : register(t0);
TextureCube mat_exposure_map : register(t1);

SamplerState smpl : register(s0);


float4		frag(float4 pos : SV_POSITION, float3 world_pos : POSITION) : SV_TARGET
{
	float3 env_map = mat_env_map.Sample(smpl, world_pos).xyz;
	float exposure = mat_exposure_map.Sample(smpl, world_pos).x * skybox_exposure;
	
	float4 color = float4(lerp(env_map, srgb_to_linear(env_map, cam_gamma), skybox_srgb) * skybox_color, exposure);
	
	return (color);
}