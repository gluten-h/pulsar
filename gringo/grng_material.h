#pragma once

#include "grng_component.h"
#include "grng_def.h"
#include "grng_material_def.h"


class grng_material : public GRNG_COMPONENT
{
public:
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


	grng_material() : GRNG_COMPONENT()
	{
		this->type = GRNG_COMPONENT_TYPE::MATERIAL;
	}

	static GRNG_COMPONENT		*create_manager_ptr()
	{
		grng_material *mat = new grng_material;

		return (mat);
	}
};

using GRNG_MATERIAL = grng_material;
