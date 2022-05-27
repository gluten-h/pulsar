
#include "gamma_correction.hlsli"
#include "normal_mapping.hlsli"


Texture2D   mat_albedo_map : register(t0);
Texture2D	mat_normal_map : register(t1);
Texture2D	mat_roughness_map : register(t2);
Texture2D	mat_metalness_map : register(t3);
Texture2D	mat_ao_map : register(t4);
Texture2D	mat_exposure_map :register(t5);

SamplerState smplr : register(s0);

cbuffer material_cb : register(b0)
{
	float3	mat_albedo_color;
	bool	mat_albedo_map_srgb;

	float	mat_normal_factor;
	float	mat_roughness;
	float	mat_metalness;
	float	mat_ao;
	float	mat_exposure;
	
	float3	pd;
};

struct fs_out
{
	float4	position : SV_Target0;
	float4	albedo : SV_Target1;
	float4	normal : SV_Target2;
	float4	rmae : SV_Target3;
};


fs_out	frag(float4 pos : SV_POSITION, float4 world_pos : POSITION, float3 normal : NORMAL, float2 uv : UV, float3 tangent : TANGENT0, float3 bitangent : TANGENT1) : SV_TARGET
{
	fs_out output;

	float3 normal_map_value = mat_normal_map.Sample(smplr, uv);
	float3 normal_m = normal_mapping(tangent, bitangent, normal, normal_map_value, mat_normal_factor);
	float exposure = mat_exposure_map.Sample(smplr, uv).x * mat_exposure;
	
	output.position = world_pos;
	output.albedo = float4(mat_albedo_map.Sample(smplr, uv).xyz * mat_albedo_color, mat_albedo_map_srgb);
	output.normal = float4(normal_m, 1.0f);
	output.rmae = float4(mat_roughness_map.Sample(smplr, uv).x * mat_roughness, mat_metalness_map.Sample(smplr, uv).x * mat_metalness, mat_ao_map.Sample(smplr, uv).x * mat_ao, exposure);

	return (output);
}
