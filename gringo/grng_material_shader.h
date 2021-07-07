#pragma once

#include "grng_def.h"
#include "grng_material_def.h"


struct				grng_shader_material
{
	XMFLOAT3		albedo_color = XMFLOAT3(1.0f, 1.0f, 1.0f);
	bool			albedo_map_srgb;

	float			normal_factor = 1.0f;
	float			padding1[3];

	float			roughness = 1.0f;
	float			padding2[3];

	float			metalness = 1.0f;
	float			padding3[3];

	float			ao = 1.0f;
	float			padding4[3];
};

using GRNG_SHADER_MATERIAL = grng_shader_material;
