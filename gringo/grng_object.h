#pragma once

#include "grng_entity.h"
#include "grng_mesh.h"
#include "grng_material.h"
#include "grng_sampler.h"
#include "grng_gfx.h"
#include "grng_def_materials.h"
#include "grng_def_rasterizer_states.h"


class grng_object : public GRNG_ENTITY
{
private:
	friend class grng_manager_ptr;

private:
	GRNG_MESH 				*mesh = NULL;
	GRNG_MATERIAL			*material = (GRNG_MATERIAL*)&GRNG_STD_MATERIAL;
	GRNG_RASTERIZER_STATE	*rs = (GRNG_RASTERIZER_STATE*)&GRNG_STD_BACK_FACE_CULL_RS;

	static GRNG_SAMPLER										material_sampler;


	static GRNG_ENTITY		*create_manager_ptr()
	{
		grng_object *obj = new grng_object;

		return (obj);
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

	void		draw() override
	{
		if (!this->mesh || !this->material)
			return;

		for (auto &b : this->bindables)
			b->bind();

		this->transform.bind();
		this->material->bind();
		this->material_sampler.bind();

		this->rs->bind();
		this->mesh->bind();
		this->mesh->draw();
	}
};

using GRNG_OBJECT = grng_object;
