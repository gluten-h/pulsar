#pragma once

#include "grng_component.h"
#include "grng_def_textures.h"
#include "grng_material_shader.h"
#include "grng_frag_const_buffer.h"


class grng_material : public GRNG_COMPONENT
{
private:
	friend class grng_manager_ptr;

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

	void		bind()
	{
		grng_material::mat_shader.albedo_color = this->albedo_color;
		grng_material::mat_shader.albedo_map_srgb = this->albedo_map_srgb;
		grng_material::mat_shader.normal_factor = this->normal_factor;
		grng_material::mat_shader.roughness = this->roughness;
		grng_material::mat_shader.metalness = this->metalness;
		grng_material::mat_shader.ao = this->ao;
		grng_material::mat_shader.exposure = this->exposure;

		grng_material::mat_cbuffer.update(grng_material::mat_shader);
		grng_material::mat_cbuffer.bind();

		this->albedo_map.bind();
		this->normal_map.bind();
		this->roughness_map.bind();
		this->metalness_map.bind();
		this->ao_map.bind();
		this->exposure_map.bind();
	}

private:
	static GRNG_COMPONENT		*create_manager_ptr()
	{
		grng_material *mat = new grng_material;

		return (mat);
	}
};

using GRNG_MATERIAL = grng_material;
