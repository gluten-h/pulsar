#pragma once

#include "grng_material_def.h"


struct				grng_material
{
	GRNG_TEXTURE	albedo_map = GRNG_TEXTURE(GRNG_STD_QUAD_WHITE, GRNG_MATERIAL_ALBEDO_MAP_SLOT);
	XMFLOAT3		albedo_color = XMFLOAT3(1.0f, 1.0f, 1.0f);
	bool			albedo_map_srgb = true;

	GRNG_TEXTURE	normal_map = GRNG_TEXTURE(GRNG_STD_QUAD_NORMAL, GRNG_MATERIAL_NORMAL_MAP_SLOT);
	float			normal_factor = 1.0f;

	GRNG_TEXTURE	roughness_map = GRNG_TEXTURE(GRNG_STD_QUAD_WHITE, GRNG_MATERIAL_ROUGHNESS_MAP_SLOT);
	float			roughness = 1.0f;

	GRNG_TEXTURE	metalness_map = GRNG_TEXTURE(GRNG_STD_QUAD_WHITE, GRNG_MATERIAL_METALNESS_MAP_SLOT);
	float			metalness = 1.0f;

	GRNG_TEXTURE	ao_map = GRNG_TEXTURE(GRNG_STD_QUAD_BLACK, GRNG_MATERIAL_AO_MAP_SLOT);
	float			ao = 1.0f;
};

using GRNG_MATERIAL = grng_material;


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
