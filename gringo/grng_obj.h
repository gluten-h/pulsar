#pragma once

#include "grng_drawable.h"
#include "grng_mesh.h"
#include "grng_components.h"
#include "grng_gfx.h"


class grng_obj : public GRNG_DRAWABLE
{
private:
	GRNG_MESH	*mesh = NULL;

public:
	GRNG_COMPONENT_TRANSFORM	transform;


	grng_obj() : GRNG_DRAWABLE()
	{

	}
	grng_obj(const grng_component_transform &transform) : GRNG_DRAWABLE()
	{
		this->transform = transform;
	}

	void	add_mesh(GRNG_MESH &mesh)
	{
		this->mesh = &mesh;
	}


	void	draw() override
	{
		for (auto &b : this->bindables)
		{
			b->bind();
		}

		this->transform.update_transform_matrix();
		this->vert_transform.world = this->transform.get_transform_matrix();
		this->vert_transform.view = GRNG_GFX::get_camera().get_view_matrix();
		this->vert_transform.proj = GRNG_GFX::get_camera().get_proj_matrix();

		this->transform_cbuffer.update(this->vert_transform);
		this->transform_cbuffer.bind();

		this->mesh->bind();
		this->mesh->draw();
	}
};

using GRNG_OBJ = grng_obj;
