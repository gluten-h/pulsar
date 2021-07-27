#pragma once

#include "grng_id3d.h"


struct grng_skybox_material_shader
{
	XMFLOAT3	env_map_color;
	bool		env_map_srgb;

	float		cam_gamma;
	float		exposure;
	float		pd0[2];
};

using GRNG_SKYBOX_MATERIAL_SHADER = grng_skybox_material_shader;
