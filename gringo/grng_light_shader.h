#pragma once

#include "grng_id3d.h"
#include "grng_def_scene.h"


typedef struct			grng_shader_light			//	TODO: MOVE IT TO ANOTHER FILE
{
	int					type;
	float				pd0[3];

	XMFLOAT3			pos;
	float				pd1[1];

	XMFLOAT3			dir;
	float				pd2[1];

	XMFLOAT3			color;
	float				pd3[1];

	XMFLOAT4			attenuation;
}						GRNG_SHADER_LIGHT;


typedef struct			grng_shader_light_scene			//	TODO: MOVE IT TO ANOTHER FILE
{
	int					light_count;
	int					pd0[3];

	GRNG_SHADER_LIGHT	light[GRNG_MAX_LIGHT_COUNT];
}						GRNG_SHADER_LIGHT_SCENE;
