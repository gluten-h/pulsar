
#include "gamma_correction.hlsli"
#include "oren_nayar.hlsli"
#include "cook_torrance.hlsli"

#include "cubemap.hlsli"
#include "texture_atlas.hlsli"


Texture2D gb_position : register(t0);
Texture2D gb_albedo : register(t1);
Texture2D gb_surface_normal : register(t2);
Texture2D gb_normal : register(t3);
Texture2D gb_rmae : register(t4);
Texture2D gb_irradiance : register(t5);

Texture2D shadow_atlas : register(t6);
Texture3D shadow_filter : register(t7);

SamplerState smplr : register(s0);
SamplerState shadow_smplr : register(s1);


#define MAX_LIGHTS_COUNT 256

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

	float4 shadow_map_uv[6];
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


static const float2 WIN_SIZE = float2(1280.0f, 720.0f);
static const float2 SA_TEXEL_SIZE = float2(1.0f / 6144.f, 1.0f / 6144.f);
static const float2 TEXEL_SIZE = float2(1.0f / 2048.0f, 1.0f / 2048.0f);
static const int FILTER_SIZE = 32;
static const int FILTER_SAMPLES = 8;
static const float FILTER_TEXEL_SIZE = 1.0f / float(FILTER_SAMPLES * FILTER_SAMPLES);
static const float FILTER_RADIUS = 8.0f;


float pcf_random(float2 frag_coord, float light_dist, float2 shadow_uv, float4 shadow_uv_rect, float n_dot_l)
{
	float2 rem = fmod(frag_coord, float2(FILTER_SIZE, FILTER_SIZE)) / float2(FILTER_SIZE, FILTER_SIZE);
	float3 offset_coord = float3(0.0f, rem.y, rem.x);
	int filter_samples_count = FILTER_SAMPLES * FILTER_SAMPLES;

	float2 uv_offset;
	float depth;
	float shadow_factor_total = 0.0f;
	float shadow_factor = 0.0f;

	for (int i = 0; i < FILTER_SAMPLES; i++)
	{
		offset_coord.x += FILTER_TEXEL_SIZE;
		float2 shadow_offsets = shadow_filter.Sample(shadow_smplr, offset_coord).xy * FILTER_RADIUS;
		uv_offset = float2(shadow_offsets.x * SA_TEXEL_SIZE.x, shadow_offsets.y * SA_TEXEL_SIZE.y);
		depth = point_sample_texture_atlas(shadow_atlas, shadow_smplr, shadow_uv_rect, shadow_uv + uv_offset).x;
		shadow_factor_total += step(light_dist, depth);
	}

	shadow_factor = shadow_factor_total / float(FILTER_SAMPLES);
	if (shadow_factor == 0.0f || shadow_factor == 1.0f || n_dot_l == 0.0f)
		return (shadow_factor);

	for (int i = FILTER_SAMPLES; i < filter_samples_count; i++)
	{
		offset_coord.x += FILTER_TEXEL_SIZE;
		float2 shadow_offsets = shadow_filter.Sample(shadow_smplr, offset_coord).xy * FILTER_RADIUS;
		uv_offset = float2(shadow_offsets.x * SA_TEXEL_SIZE.x, shadow_offsets.y * SA_TEXEL_SIZE.y);
		depth = point_sample_texture_atlas(shadow_atlas, shadow_smplr, shadow_uv_rect, shadow_uv + uv_offset).x;
		shadow_factor_total += step(light_dist, depth);
	}
	shadow_factor = shadow_factor_total / float(filter_samples_count);

	return (shadow_factor);
}


//float pcf(float light_dist, float2 shadow_uv, float4 shadow_uv_rect, float filter_size)
//{
//	float shadow_factor = 0.0f;

//	float half_filter_size = filter_size * 0.5;
//	for (float y = -half_filter_size; y < -half_filter_size + filter_size; y++)
//	{
//		for (float x = -half_filter_size; x < -half_filter_size + filter_size; x++)
//		{
//			float2 uv_offset = float2(x * SA_TEXEL_SIZE.x, y * SA_TEXEL_SIZE.y) * FILTER_RADIUS;
//			float2 moments = point_sample_texture_atlas(shadow_atlas, shadow_smplr, shadow_uv_rect, shadow_uv + uv_offset).xy;
	
//			//shadow_factor += variance_shadow_mapping(moments, light_dist);
//			//shadow_factor += step(light_dist, moments.x - 0.0002f);
//		}
//	}

//	return (shadow_factor / (filter_size * filter_size));

//	//float total_samples = filter_size * 2.0f + 1.0f;
//	//return (shadow_factor / (total_samples * total_samples));
//}

//float2 pcss_blocker_distance(float receiver_dist, float2 shadow_uv, float4 shadow_uv_rect)
//{
//	const float PCSS_BLOCKER_AREA_SIZE = 2.0f;
//	//const float PCSS_BLOCKER_AREA_START = (PCSS_BLOCKER_AREA_SIZE - 1.0f) / 2.0f;

//	float blockers_count = 0.0f;
//	float avg_blocker_dist = 0.0f;

//	for (float y = -PCSS_BLOCKER_AREA_SIZE; y <= PCSS_BLOCKER_AREA_SIZE; y += 1.0f)
//	{
//		for (float x = -PCSS_BLOCKER_AREA_SIZE; x <= PCSS_BLOCKER_AREA_SIZE; x += 1.0f)
//		{
//			float2 uv_offset = float2(x * TEXEL_SIZE.x, y * TEXEL_SIZE.y);

//			float blocker_dist = point_sample_texture_atlas(shadow_atlas, shadow_smplr, shadow_uv_rect, shadow_uv + uv_offset).x;
//			if (blocker_dist < receiver_dist)
//			{
//				blockers_count += 1.0f;
//				avg_blocker_dist += blocker_dist;
//			}
//		}
//	}
//	avg_blocker_dist /= blockers_count;

//	return (float2(avg_blocker_dist, blockers_count));
//}

//float	pcss(float3 light_dir, float receiver_dist, int light_id)
//{
//	uint face_id;
//	float2 shadow_uv = sample_cubemap(-light_dir, face_id);
//	float4 shadow_uv_rect = l_scene.lights[light_id].shadow_map_uv[face_id];

//	float2 avg_blocker = pcss_blocker_distance(receiver_dist, shadow_uv, shadow_uv_rect);
//	if (avg_blocker.y < 1.0f || avg_blocker.x < 0.2f)
//		return (1.0f);

//	float penumbra_size = 1.0f * (receiver_dist - avg_blocker.x) / avg_blocker.x;
//	penumbra_size = clamp(penumbra_size * 10.0f, 0.0f, 5.0f);
//	float shadow_factor = pcf(receiver_dist, shadow_uv, shadow_uv_rect, penumbra_size);

//	return (shadow_factor);
//	//return (float3(avg_blocker.xy, penumbra_size));
//}


float4 frag(float4 sv_pos : SV_POSITION, float2 uv : UV) : SV_TARGET
{
	float3 pos = gb_position.Sample(smplr, uv).xyz;
	float3 albedo = gb_albedo.Sample(smplr, uv).xyz;
	albedo = lerp(albedo, srgb_to_linear(albedo, cam_gamma), gb_albedo.Sample(smplr, uv).w);
	float3 surface_normal = gb_surface_normal.Sample(smplr, uv).xyz;
	float3 normal = gb_normal.Sample(smplr, uv).xyz;

	float4 rmae = gb_rmae.Sample(smplr, uv);
	float roughness = rmae.x;
	float metalness = rmae.y;
	float ao = rmae.z;
	float exposure = rmae.w;
	float irradiance = gb_irradiance.Sample(smplr, uv);
	// !!! IOR !!!

	float3 view_dir = normalize(cam_pos - pos);
	float3 ambient = irradiance * albedo * ao;
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

		float3 F = fresnel_schlick(max(0.0f, dot(halfway_dir, view_dir)), F0, roughness);
		float3 k_spec = F;
		float3 k_diff = float3(1.0f, 1.0f, 1.0f) - k_spec;
		k_diff *= (1.0f - metalness);

		float3 diff_brdf = oren_nayar(view_dir, light_dir, normal, albedo, roughness);
		float3 spec_brdf = cook_torrance(view_dir, light_dir, halfway_dir, normal, F, roughness);

		//float light_dist = length(l_scene.lights[i].pos_dir - pos);
		float3 shadow_pos = pos + surface_normal * lerp(0.002, 0.075, 1.0f - n_dot_l);
		float light_dist = length(l_scene.lights[i].pos_dir - shadow_pos);

		uint face_id;
		float2 shadow_uv = sample_cubemap(-light_dir, face_id);
		float shadow_factor = pcf_random(float2(uv.x * WIN_SIZE.x, uv.y * WIN_SIZE.y), light_dist, shadow_uv, l_scene.lights[i].shadow_map_uv[face_id], n_dot_l);

		color += float4((k_diff * diff_brdf + spec_brdf) * radiance * n_dot_l, 1.0f) * shadow_factor;
	}
	color = float4(color.xyz, exposure);

	return (color);
}
