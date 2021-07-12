#pragma once

#include "grng_entity.h"
#include "grng_mesh.h"
#include "grng_material.h"
#include "grng_material_shader.h"
#include "grng_sampler.h"
#include "grng_gfx.h"
#include "grng_def.h"


class grng_object : public GRNG_ENTITY
{
private:
	GRNG_MESH 				*mesh = NULL;
	GRNG_RASTERIZER_STATE	*rs = (GRNG_RASTERIZER_STATE*)&GRNG_STD_BACK_FACE_CULL_RS;

	static GRNG_FRAG_CONST_BUFFER<GRNG_SHADER_MATERIAL>		material_cbuffer;
	static GRNG_SAMPLER										material_sampler;

	GRNG_SHADER_MATERIAL									shader_material;
	GRNG_MATERIAL											*material = NULL;


	void		update_transform()
	{
		this->transform.update_transform_matrix();
		this->vert_transform.model = this->transform.get_transform_matrix();
		this->vert_transform.view = GRNG_GFX::get_curr_camera()->get_view_matrix();
		this->vert_transform.proj = GRNG_GFX::get_curr_camera()->get_proj_matrix();
		this->vert_transform.norm = XMMatrixTranspose(XMMatrixInverse(NULL, this->vert_transform.model));

		grng_object::transform_cbuffer.update(this->vert_transform);
		grng_object::transform_cbuffer.bind();
	}

	void		update_material()
	{
		this->shader_material.albedo_color = this->material->albedo_color;
		this->shader_material.albedo_map_srgb = this->material->albedo_map_srgb;
		this->shader_material.normal_factor = this->material->normal_factor;
		this->shader_material.roughness = this->material->roughness;
		this->shader_material.metalness = this->material->metalness;
		this->shader_material.ao = this->material->ao;

		grng_object::material_cbuffer.update(this->shader_material);
		grng_object::material_cbuffer.bind();

		this->material->albedo_map.bind();
		this->material->normal_map.bind();
		this->material->roughness_map.bind();
		this->material->metalness_map.bind();
		this->material->ao_map.bind();

		grng_object::material_sampler.bind();
	}

public:
	grng_object() : GRNG_ENTITY()
	{
		this->type = GRNG_ENTITY_TYPE::OBJECT;
	}
	grng_object(const GRNG_TRANSFORM &transform) : GRNG_ENTITY()
	{
		this->type = GRNG_ENTITY_TYPE::OBJECT;
		this->transform = transform;
	}


	void		set_mesh(const GRNG_MESH &mesh)
	{
		this->mesh = (GRNG_MESH*)&mesh;
	}

	void		set_rasterizer_state(const GRNG_RASTERIZER_STATE &rs)
	{
		this->rs = (GRNG_RASTERIZER_STATE*)&rs;
	}

	void		set_material(const GRNG_MATERIAL &material)
	{
		this->material = (GRNG_MATERIAL*)&material;
	}


	static GRNG_ENTITY		*create_manager_ptr()
	{
		grng_object *obj = new grng_object;

		return (obj);
	}


	void		draw() override
	{
		if (!this->mesh)
			return;

		for (auto &b : this->bindables)
			b->bind();

		this->update_transform();
		this->update_material();

		this->rs->bind();
		this->mesh->bind();
		this->mesh->draw();
	}
};

using GRNG_OBJECT = grng_object;
