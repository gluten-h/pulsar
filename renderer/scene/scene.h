#pragma once

//#include "fixed_vector.h"
//#include "config/scene.h"
//#include "scene_manager.h"
//#include "entity.h"
//#include "light.h"
//#include "skybox.h"
//#include "const_buffers/frag_const_buffer.h"
//#include "dynamic_const_buffers/vert_dynamic_const_buffer.h"

#include "ecs/registry.h"


namespace PULSAR
{
	class node;

	class scene
	{
	private:
		friend class node;

	private:
		static scene *mp_active_scene;

	private:
		//PULSAR::ENTITY_MANAGER		entity_manager;
		//PULSAR::LIGHT_MANAGER		light_manager;

		//PULSAR::SHADER_LIGHT_SCENE								light_scene;
		//PULSAR::frag_const_buffer<PULSAR::SHADER_LIGHT_SCENE>	light_scene_cbuffer;

		//PULSAR::SKYBOX		skybox;


		PULSAR::ecs::registry m_registry;

		PULSAR::node *mp_main_camera = NULL;

	public:
		static void		set_active_scene(PULSAR::scene *scene);
		static scene	*get_active_scene();

	public:
		scene &operator=(const scene&) = delete;
		scene &operator=(scene&&) = delete;
		scene(const scene&) = delete;
		scene(scene&&) = delete;
		scene() = default;
		~scene() = default;

		//void	update_shader_light_scene()
		//{
		//	this->light_scene.light_count = this->light_manager.size();
		//	this->light_scene_cbuffer.set_slot(DEFERRED_LIGHT_SLOT);
		//
		//	int i = 0;
		//	for (auto &it : this->light_manager)
		//	{
		//		it.data->set_shader_light(this->light_scene.light[i++]);
		//	}
		//}

		PULSAR::node	create_node();

		PULSAR::node	*get_main_camera();
		void	set_main_camera(PULSAR::node *camera);

		const PULSAR::ecs::registry	&registry() const;

		//void	add_light(PULSAR::LIGHT *light);
		//void	remove_light(PULSAR::LIGHT *light);
		//void	remove_light(unsigned int id);
		//PULSAR::LIGHT	*get_light(unsigned int id);

		//void	set_skybox_material(const PULSAR::SKYBOX_MATERIAL &mat);
		//void	set_skybox_material(PULSAR::SKYBOX_MATERIAL *mat);
		//void	set_skybox_mesh(const PULSAR::mesh &mesh);
		//void	set_skybox_mesh(PULSAR::mesh *mesh);

		void	draw();
		void	draw_skybox();

		//void	bind()
		//{
		//	this->update_shader_light_scene();
		//	this->light_scene_cbuffer.update(this->light_scene);
		//	this->light_scene_cbuffer.bind();
		//}
	};
}
