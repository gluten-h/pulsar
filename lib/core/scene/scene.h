#pragma once

#include "piston.h"
#include "def_scene.h"
#include "scene_manager.h"
#include "entity.h"
#include "light.h"
#include "skybox.h"
#include "frag_const_buffer.h"


namespace PULSAR
{
	class SCENE
	{
	private:
		int		id = -1;
		bool	is_alloc = false;

		PULSAR::ENTITY_MANAGER												entity_manager;
		const PULSAR::IPISTON<PULSAR::ENTITY*, PULSAR::MAX_ENTITY_COUNT>	*ientity = this->entity_manager.get_idata();

		PULSAR::LIGHT_MANAGER												light_manager;
		const PULSAR::IPISTON<PULSAR::LIGHT*, PULSAR::MAX_LIGHT_COUNT>		*ilight = this->light_manager.get_idata();

		PULSAR::SHADER_LIGHT_SCENE									light_scene;
		PULSAR::FRAG_CONST_BUFFER<PULSAR::SHADER_LIGHT_SCENE>		light_scene_cbuffer;

		PULSAR::SKYBOX		skybox;

	public:
		SCENE	&operator=(const SCENE &s) = delete;
		SCENE(const SCENE &s) = delete;
		SCENE(){ }

		int		get_id() const
		{
			return (this->id);
		}

		void	update_shader_light_scene()
		{
			this->light_scene.light_count = this->ilight->size;
			this->light_scene_cbuffer.set_slot(DEFERRED_LIGHT_SLOT);

			int i = -1;
			while (++i < this->ilight->size)
			{
				LIGHT *light_ptr = this->light_manager.get_data_secure(this->ilight->data[i].global_id);
				light_ptr->set_shader_light(this->light_scene.light[i]);
			}
		}

		void	add_entity(PULSAR::ENTITY *entity);
		void	remove_entity(PULSAR::ENTITY *entity);
		void	remove_entity(unsigned int id);
		PULSAR::ENTITY		*get_entity(unsigned int id);

		void	add_light(PULSAR::LIGHT *light);
		void	remove_light(PULSAR::LIGHT *light);
		void	remove_light(unsigned int id);
		PULSAR::LIGHT		*get_light(unsigned int id);

		void	set_skybox_material(const PULSAR::SKYBOX_MATERIAL &mat);
		void	set_skybox_material(PULSAR::SKYBOX_MATERIAL *mat);
		void	set_skybox_mesh(const PULSAR::MESH &mesh);
		void	set_skybox_mesh(PULSAR::MESH *mesh);

		static SCENE	*create()
		{
			SCENE *scene = new SCENE;
			scene->id = PULSAR::SM.add(scene);
			if (scene->id == -1)
			{
				delete scene;
				return (NULL);
			}
			scene->is_alloc = true;

			return (scene);
		}

		void	draw();
		void	draw_skybox();

		void	bind()
		{
			this->update_shader_light_scene();
			this->light_scene_cbuffer.update(this->light_scene);
			this->light_scene_cbuffer.bind();
		}
	};
}
