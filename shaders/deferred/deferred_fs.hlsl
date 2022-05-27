
#include "gamma_correction.hlsli"
#include "oren_nayar.hlsli"
#include "cook_torrance.hlsli"


Texture2D gb_position : register(t0);
Texture2D gb_albedo : register(t1);
Texture2D gb_normal : register(t2);
Texture2D gb_rmae : register(t3);

SamplerState smplr : register(s0);


#define MAX_LIGHTS_COUNT 1024

#define POINT_LIGHT 0
#define DIR_LIGHT 1

#define CT_F0 0.04f


struct light_specs
{
	int type;
	float3 pos_dir;

	float3 color;
	float pd0;

	float const_att;
	float linear_att;
	float quad_att;
	float pd1;
};

struct light_scene
{
	int lights_count;
	float3 pd0;
	
	light_specs lights[MAX_LIGHTS_COUNT];
};

cbuffer light_scene_cb : register(b0)
{
	light_scene l_scene;
};


cbuffer camera_cb : register(b1)
{
	float3 cam_pos;
	float cam_gamma;
	
	float3 cam_dir;
	float cam_exposure;
};


float4		frag(float4 sv_pos : SV_POSITION, float2 uv : UV) : SV_TARGET
{
	float3 pos = gb_position.Sample(smplr, uv).xyz;
	float3 albedo = gb_albedo.Sample(smplr, uv).xyz;
	albedo = lerp(albedo, srgb_to_linear(albedo, cam_gamma), gb_albedo.Sample(smplr, uv).w);
	float3 normal = gb_normal.Sample(smplr, uv).xyz;
	
	float4 rmae = gb_rmae.Sample(smplr, uv);
	float roughness = rmae.x;
	float metalness = rmae.y;
	float ao = rmae.z;
	float exposure = rmae.w;
	
	float3 view_dir = normalize(cam_pos - pos);
	float3 ambient = albedo * ao;
	float4 color = float4(ambient.xyz, 1.0f);
	
	float3 F0 = float3(CT_F0, CT_F0, CT_F0);
	F0 = lerp(F0, albedo, metalness);

	for (int i = 0; i < l_scene.lights_count; i++)
	{
		float3 light_dir = float3(0.0f, 0.0f, 0.0f);
		float attenuation = 1.0f;
		float3 radiance = l_scene.lights[i].color.xyz;
		
		switch (l_scene.lights[i].type)
		{
			case POINT_LIGHT:
			{
				light_dir = normalize(l_scene.lights[i].pos_dir - pos);
				float dist = length(l_scene.lights[i].pos_dir - pos);
				attenuation = 1.0f / (l_scene.lights[i].const_att + l_scene.lights[i].linear_att * dist + l_scene.lights[i].quad_att * (dist * dist));
				radiance = l_scene.lights[i].color.xyz * attenuation;
				
				break;
			}
			case DIR_LIGHT:
			{
				light_dir = -l_scene.lights[i].pos_dir;
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
	color = float4(color.xyz, exposure);
	
	return (color);
}
