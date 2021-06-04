
#include "point_light.hlsli"
#include "dir_light.hlsli"


Texture2D gb_position : register(t0);
Texture2D gb_albedo : register(t1);
Texture2D gb_normal : register(t2);

SamplerState smpl : register(s0);


#define MAX_LIGHT_COUNT 128

#define POINT_LIGHT 0
#define DIR_LIGHT 1


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
};


float4		frag(float4 sv_pos : SV_POSITION, float2 uv : UV) : SV_TARGET
{
	float3 pos = gb_position.Sample(smpl, uv);
	float3 albedo = gb_albedo.Sample(smpl, uv);
	float3 normal = gb_normal.Sample(smpl, uv);
	float4 color = float4(0.0f, 0.0f, 0.0f, 0.0f);

	for (int i = 0; i < l_scene.light_count; i++)
	{
		float3 l_dir = float3(0.0f, 0.0f, 0.0f);

		switch (l_scene.light[i].type)
		{
			case POINT_LIGHT:
			{
				l_dir = get_point_light_dir(l_scene.light[i].pos, pos);
				break;
			}
			case DIR_LIGHT:
			{
				l_dir = get_dir_light_dir(l_scene.light[i].dir);
				break;
			}

			default:
			break;
		}

		float cost = saturate(dot(l_dir, normal));
		color += float4(albedo * cost, 1.0f);
	}

	//color = abs(float4(l_scene.light[i].dir, 1.0f));

	return (color);
}
