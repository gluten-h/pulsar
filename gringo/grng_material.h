#pragma once

#include "grng_component.h"
#include "grng_def_textures.h"
#include "grng_material_shader.h"
#include "grng_frag_const_buffer.h"


class grng_material : public GRNG_COMPONENT
{
private:
	static GRNG_MATERIAL_SHADER								mat_shader;
	static GRNG_FRAG_CONST_BUFFER<GRNG_MATERIAL_SHADER>		mat_cbuffer;

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

	GRNG_TEXTURE	ao_map = GRNG_STD_QUAD_WHITE_TEX;
	float			ao = 0.0f;

	GRNG_TEXTURE	exposure_map = GRNG_STD_QUAD_WHITE_TEX;
	float			exposure = 1.0f;

	GRNG_TEXTURE	irradiance_map = GRNG_STD_QUAD_WHITE_TEX;
	float			irradiance = 0.0f;


	grng_material	&operator=(const grng_material &m) = delete;
	grng_material(const grng_material &m) = delete;
	grng_material() : GRNG_COMPONENT()
	{
		this->type = GRNG_COMPONENT_TYPE::MATERIAL;

		this->albedo_map.set_slot(GRNG_MATERIAL_ALBEDO_MAP_SLOT);
		this->normal_map.set_slot(GRNG_MATERIAL_NORMAL_MAP_SLOT);
		this->roughness_map.set_slot(GRNG_MATERIAL_ROUGHNESS_MAP_SLOT);
		this->metalness_map.set_slot(GRNG_MATERIAL_METALNESS_MAP_SLOT);
		this->ao_map.set_slot(GRNG_MATERIAL_AO_MAP_SLOT);
		this->exposure_map.set_slot(GRNG_MATERIAL_EXPOSURE_MAP_SLOT);
	}

	static grng_material	*create()
	{
		grng_material *mat = new grng_material;
		mat->id = GRNG_CM.add(mat);
		if (mat->id == -1)
		{
			delete mat;
			return (NULL);
		}
		mat->is_alloc = true;

		return (mat);
	}

	void		bind(GRNG_BIND_SCOPE scope)
	{
		grng_material::mat_shader.albedo_color = this->albedo_color;
		grng_material::mat_shader.albedo_map_srgb = this->albedo_map_srgb;
		grng_material::mat_shader.normal_factor = this->normal_factor;
		grng_material::mat_shader.roughness = this->roughness;
		grng_material::mat_shader.metalness = this->metalness;
		grng_material::mat_shader.ao = this->ao;
		grng_material::mat_shader.exposure = this->exposure;

		grng_material::mat_cbuffer.update(grng_material::mat_shader);
		grng_material::mat_cbuffer.bind(scope);

		this->albedo_map.bind(scope);
		this->normal_map.bind(scope);
		this->roughness_map.bind(scope);
		this->metalness_map.bind(scope);
		this->ao_map.bind(scope);
		this->exposure_map.bind(scope);
	}
};

using GRNG_MATERIAL = grng_material;
