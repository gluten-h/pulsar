#pragma once

#include "bindable_entity.h"
#include "scene.h"
#include "mesh.h"
#include "material.h"
#include "sampler.h"
#include "gfx.h"
#include "def_materials.h"
#include "def_rasterizer_states.h"
#include "transform.h"


namespace PULSAR
{
	class OBJECT : public PULSAR::BINDABLE_ENTITY
	{
	private:
		PULSAR::MESH				*mesh = NULL;
		PULSAR::MATERIAL			*material = (PULSAR::MATERIAL*)&PULSAR::STD_MATERIAL;
		PULSAR::RASTERIZER_STATE	*rs = (PULSAR::RASTERIZER_STATE*)&PULSAR::STD_BACK_FACE_CULL_RS;

		static SAMPLER		material_sampler;


		void		remove_from_scenes()
		{
			for (auto &it : this->scene_local_id)
			{
				PULSAR::SCENE *scene_ptr = PULSAR::SCENE_MANAGER::get_instance().get_elem(it.first);
				if (scene_ptr)
					scene_ptr->remove_entity(it.second);
			}
			this->scene_local_id.clear();
		}

	public:
		PULSAR::TRANSFORM	transform;


		OBJECT() : PULSAR::BINDABLE_ENTITY()
		{
			this->type = PULSAR::ENTITY_TYPE::OBJECT;
		}
		OBJECT(const PULSAR::TRANSFORM &transform) : PULSAR::BINDABLE_ENTITY()
		{
			this->type = PULSAR::ENTITY_TYPE::OBJECT;
			this->transform = transform;
		}
		~OBJECT()
		{
			this->destroy();
		}

		void	set_mesh(const PULSAR::MESH &mesh)
		{
			this->mesh = (PULSAR::MESH*)&mesh;
		}
		void	set_mesh(PULSAR::MESH *mesh)
		{
			this->mesh = mesh;
		}

		void	set_rasterizer_state(const PULSAR::RASTERIZER_STATE &rs)
		{
			this->rs = (PULSAR::RASTERIZER_STATE *)&rs;
		}
		void	set_rasterizer_state(PULSAR::RASTERIZER_STATE *rs)
		{
			this->rs = rs;
		}

		void	set_material(const PULSAR::MATERIAL &material)
		{
			this->material = (PULSAR::MATERIAL*)&material;
		}
		void	set_material(PULSAR::MATERIAL *material)
		{
			this->material = material;
		}

		static OBJECT	*create()
		{
			return ((PULSAR::OBJECT*)PULSAR::ENTITY::add_to_manager(new PULSAR::OBJECT));
		}

		void	destroy()
		{
			if (!this->is_alloc)
				return;
			this->is_alloc = false;

			this->remove_from_scenes();
			PULSAR::ENTITY_MANAGER::get_instance().remove(this);
			delete this;
		}

		void	draw() override
		{
			if (!this->mesh || !this->material)
				return;

			this->bind();

			this->transform.bind(PULSAR::BIND_SCOPE::LOCAL);
			this->material->bind(PULSAR::BIND_SCOPE::LOCAL);
			this->material_sampler.bind(PULSAR::BIND_SCOPE::LOCAL);

			this->rs->bind(PULSAR::BIND_SCOPE::LOCAL);
			this->mesh->bind(PULSAR::BIND_SCOPE::LOCAL);
			PULSAR::GFX::draw_indexed(this->mesh->get_index_count());


			PULSAR::BINDABLE::unbind_local();
		}
	};
}
