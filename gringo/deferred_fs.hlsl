
#include "point_light.hlsli"
#include "dir_light.hlsli"

#include "gamma_correction.hlsli"

#include "oren_nayar.hlsli"
#include "cook_torrance.hlsli"


Texture2D gb_position : register(t0);
Texture2D gb_albedo : register(t1);
Texture2D gb_normal : register(t2);
Texture2D gb_rma : register(t3);

SamplerState smpl : register(s0);


#define MAX_LIGHT_COUNT 128

#define POINT_LIGHT 0
#define DIR_LIGHT 1


#define CT_F0 0.04f


struct light_specs
{
	int			type;
	int3		pd0;

	float3		pos;
	float		pd1;

	float3		dir;
	float		pd2;

	float3		color;
	float		pd3;

	float		const_att;
	float		linear_att;
	float		quad_att;
	float		pd4;
};

struct light_scene
{
	int				light_count;
	int3			pd0;

	light_specs		light[MAX_LIGHT_COUNT];
};

cbuffer light_scene_cb : register(b0)
{
	light_scene l_scene;
};


cbuffer camera_cb : register(b1)
{
	float3		cam_pos;
	float		pd0;

	float3		cam_dir;
	float		pd1;
	
	float		cam_gamma;
	float3		pd2;
};


float4		frag(float4 sv_pos : SV_POSITION, float2 uv : UV) : SV_TARGET
{
	float3 pos = gb_position.Sample(smpl, uv).xyz;
	float3 albedo = gb_albedo.Sample(smpl, uv).xyz;
	albedo = lerp(albedo, srgb_to_linear(albedo, cam_gamma), gb_albedo.Sample(smpl, uv).w);
	float3 normal = gb_normal.Sample(smpl, uv).xyz;
	float roughness = gb_rma.Sample(smpl, uv).x;
	float metalness = gb_rma.Sample(smpl, uv).y;
	float ao = gb_rma.Sample(smpl, uv).z;
	
	float3 view_dir = normalize(cam_pos - pos);
	float3 ambient = albedo * ao;
	float4 color = float4(ambient.xyz, 1.0f);
	
	float3 F0 = float3(CT_F0, CT_F0, CT_F0);
	F0 = lerp(F0, albedo, metalness);

	for (int i = 0; i < l_scene.light_count; i++)
	{
		float3 light_dir = float3(0.0f, 0.0f, 0.0f);
		float attenuation = 1.0f;
		float3 radiance = l_scene.light[i].color.xyz;
		
		switch (l_scene.light[i].type)
		{
			case POINT_LIGHT:
			{
				light_dir = get_point_light_dir(l_scene.light[i].pos, pos);
				float dist = length(l_scene.light[i].pos - pos);
				attenuation = 1.0f / (l_scene.light[i].const_att + l_scene.light[i].linear_att * dist + l_scene.light[i].quad_att * (dist * dist));
				radiance = l_scene.light[i].color.xyz * attenuation;
				
				break;
			}
			case DIR_LIGHT:
			{
				light_dir = get_dir_light_dir(l_scene.light[i].dir);
				break;
			}

			default:
			break;
		}
		
		float3 n_dot_l = max(0.0f, dot(normal, light_dir));
		float3 halfway_dir = normalize(view_dir + light_dir);
		
		float3 F = fresnel_schlick(max(0.0f, dot(halfway_dir, view_dir)), F0);
		float3 k_spec = F;
		float3 k_diff = float3(1.0f, 1.0f, 1.0f) - k_spec;
		k_diff *= (1.0f - metalness);

		float3 diff_brdf = oren_nayar(view_dir, light_dir, normal, albedo, roughness);
		float3 spec_brdf = cook_torrance(view_dir, light_dir, halfway_dir, normal, F, roughness);
		
		color += float4((k_diff * diff_brdf + spec_brdf) * radiance * n_dot_l, 1.0f);
	}
	color = float4(gamma_correction(color.xyz, cam_gamma).xyz, 1.0f);

	return (color);
}
