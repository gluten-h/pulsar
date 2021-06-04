#pragma once

#include "grng_material_def.h"


struct				grng_material
{
	GRNG_TEXTURE	albedo = GRNG_TEXTURE(GRNG_STD_QUAD_WHITE, GRNG_MATERIAL_ALBEDO_SLOT);
	XMFLOAT3		albedo_color = XMFLOAT3(1.0f, 1.0f, 1.0f);
};

using GRNG_MATERIAL = grng_material;


struct				grng_shader_material
{
	XMFLOAT3		albedo_color = XMFLOAT3(1.0f, 1.0f, 1.0f);

	float			padding[1];
};

using GRNG_SHADER_MATERIAL = grng_shader_material;
