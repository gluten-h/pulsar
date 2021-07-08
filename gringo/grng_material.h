#pragma once

#include "grng_component.h"
#include "grng_def.h"
#include "grng_material_def.h"


class grng_material : public GRNG_COMPONENT
{
public:
	GRNG_TEXTURE	albedo_map = GRNG_STD_QUAD_WHITE_TEX;
	XMFLOAT3		albedo_color = XMFLOAT3(1.0f, 1.0f, 1.0f);
	bool			albedo_map_srgb = true;

	GRNG_TEXTURE	normal_map = GRNG_STD_QUAD_NORMAL_TEX;
	float			normal_factor = 1.0f;

	GRNG_TEXTURE	roughness_map = GRNG_STD_QUAD_WHITE_TEX;
	float			roughness = 1.0f;

	GRNG_TEXTURE	metalness_map = GRNG_STD_QUAD_WHITE_TEX;
	float			metalness = 1.0f;

	GRNG_TEXTURE	ao_map = GRNG_STD_QUAD_BLACK_TEX;
	float			ao = 1.0f;


	grng_material() : GRNG_COMPONENT()
	{
		this->type = GRNG_COMPONENT_TYPE::MATERIAL;

		this->albedo_map.set_slot(GRNG_MATERIAL_ALBEDO_MAP_SLOT);
		this->normal_map.set_slot(GRNG_MATERIAL_NORMAL_MAP_SLOT);
		this->roughness_map.set_slot(GRNG_MATERIAL_ROUGHNESS_MAP_SLOT);
		this->metalness_map.set_slot(GRNG_MATERIAL_METALNESS_MAP_SLOT);
		this->ao_map.set_slot(GRNG_MATERIAL_AO_MAP_SLOT);
	}

	static GRNG_COMPONENT		*create_manager_ptr()
	{
		grng_material *mat = new grng_material;

		return (mat);
	}
};

using GRNG_MATERIAL = grng_material;
