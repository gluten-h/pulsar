#pragma once

#include "grng_component.h"
#include "grng_skybox_material_def.h"
#include "grng_skybox_material_shader.h"
#include "grng_def_cubemaps.h"
#include "grng_frag_const_buffer.h"
#include "grng_gfx.h"


class grng_skybox_material : public GRNG_COMPONENT
{
private:
	static GRNG_SKYBOX_MATERIAL_SHADER							skybox_mat_shader;
	static GRNG_FRAG_CONST_BUFFER<GRNG_SKYBOX_MATERIAL_SHADER>	skybox_mat_cbuffer;

public:
	GRNG_CUBEMAP		env_map = GRNG_STD_CUBEMAP_BLACK;
	XMFLOAT3			env_map_color = XMFLOAT3(1.0f, 1.0f, 1.0f);
	bool				env_map_srgb = true;

	GRNG_CUBEMAP		exposure_map = GRNG_STD_CUBEMAP_WHITE;
	float				exposure = 1.0f;


	grng_skybox_material	&operator=(const grng_skybox_material &m) = delete;
	grng_skybox_material(const grng_skybox_material &m) = delete;
	grng_skybox_material() : GRNG_COMPONENT()
	{
		this->type = GRNG_COMPONENT_TYPE::SKYBOX_MATERIAL;
		this->env_map.set_slot(GRNG_SKYBOX_MATERIAL_ENV_MAP_SLOT);
		this->exposure_map.set_slot(GRNG_SKYBOX_MATERIAL_EXPOSURE_MAP_SLOT);
	}

	static grng_skybox_material		*create()
	{
		grng_skybox_material *mat = new grng_skybox_material;
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
		grng_skybox_material::skybox_mat_shader.env_map_color = this->env_map_color;
		grng_skybox_material::skybox_mat_shader.env_map_srgb = this->env_map_srgb;
		grng_skybox_material::skybox_mat_shader.cam_gamma = GRNG_GFX::get_curr_camera()->get_gamma();
		grng_skybox_material::skybox_mat_shader.exposure = this->exposure;

		grng_skybox_material::skybox_mat_cbuffer.update(grng_skybox_material::skybox_mat_shader);
		grng_skybox_material::skybox_mat_cbuffer.bind(scope);

		grng_skybox_material::env_map.bind(scope);
		grng_skybox_material::exposure_map.bind(scope);
	}
};

using GRNG_SKYBOX_MATERIAL = grng_skybox_material;
