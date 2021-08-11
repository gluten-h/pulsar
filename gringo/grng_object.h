#pragma once

#include "grng_bindable_entity.h"
#include "grng_scene.h"
#include "grng_mesh.h"
#include "grng_material.h"
#include "grng_sampler.h"
#include "grng_gfx.h"
#include "grng_def_materials.h"
#include "grng_def_rasterizer_states.h"
#include "grng_transform.h"


class grng_object : public GRNG_BINDABLE_ENTITY
{
private:
	friend class grng_manager_ptr;

private:
	GRNG_MESH 				*mesh = NULL;
	GRNG_MATERIAL			*material = (GRNG_MATERIAL*)&GRNG_STD_MATERIAL;
	GRNG_RASTERIZER_STATE	*rs = (GRNG_RASTERIZER_STATE*)&GRNG_STD_BACK_FACE_CULL_RS;

	static GRNG_SAMPLER		material_sampler;


	void		remove_from_scenes()
	{
		for (auto &it : this->scene_local_id)
		{
			GRNG_SCENE *scene = GRNG_SM.get_data_secure(it.first);
			if (scene)
				scene->remove_entity(it.second);
		}
		this->scene_local_id.clear();
	}

public:
	GRNG_TRANSFORM		transform;


	grng_object() : GRNG_BINDABLE_ENTITY()
	{
		this->type = GRNG_ENTITY_TYPE::OBJECT;
	}
	grng_object(const GRNG_TRANSFORM &transform) : GRNG_BINDABLE_ENTITY()
	{
		this->type = GRNG_ENTITY_TYPE::OBJECT;
		this->transform = transform;
	}
	~grng_object()
	{
		this->destroy();
	}

	void		set_mesh(const GRNG_MESH &mesh)
	{
		this->mesh = (GRNG_MESH*)&mesh;
	}
	void		set_mesh(GRNG_MESH *mesh)
	{
		this->mesh = mesh;
	}

	void		set_rasterizer_state(const GRNG_RASTERIZER_STATE &rs)
	{
		this->rs = (GRNG_RASTERIZER_STATE*)&rs;
	}
	void		set_rasterizer_state(GRNG_RASTERIZER_STATE *rs)
	{
		this->rs = rs;
	}

	void		set_material(const GRNG_MATERIAL &material)
	{
		this->material = (GRNG_MATERIAL*)&material;
	}
	void		set_material(GRNG_MATERIAL *material)
	{
		this->material = material;
	}

	static grng_object		*create()
	{
		grng_object *obj = new grng_object;
		obj->id = GRNG_EM.add(obj);
		if (obj->id == -1)
		{
			delete obj;
			return (NULL);
		}
		obj->is_alloc = true;

		return (obj);
	}

	void					destroy()
	{
		if (!this->is_alloc)
			return;
		this->is_alloc = false;

		this->remove_from_scenes();
		GRNG_EM.remove_secure(this);
		delete this;
	}

	void		draw() override
	{
		if (!this->mesh || !this->material)
			return;

		this->bind();

		this->transform.bind(GRNG_BIND_SCOPE::LOCAL);
		this->material->bind(GRNG_BIND_SCOPE::LOCAL);
		this->material_sampler.bind(GRNG_BIND_SCOPE::LOCAL);

		this->rs->bind(GRNG_BIND_SCOPE::LOCAL);
		this->mesh->bind(GRNG_BIND_SCOPE::LOCAL);
		this->mesh->draw();


		GRNG_BINDABLE::unbind_local();
	}
};

using GRNG_OBJECT = grng_object;
