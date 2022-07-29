#pragma once

#include "ecs/ecs.h"
#include "light/light.h"
#include "skybox_material/skybox_material.h"
#include <vector>
#include <type_traits>


namespace pulsar
{
	class node;

	class scene
	{
	private:
		friend class node;

	private:
		static scene *mp_active_scene;

		pulsar::ecs::registry m_registry;
		std::vector<pulsar::ecs::system*> m_systems;

		pulsar::skybox_material m_skybox_material;
		pulsar::node *mp_main_camera = NULL;

	public:
		static void		set_active_scene(pulsar::scene *scene);
		static scene	*get_active_scene();

	public:
		scene &operator=(const scene&) = delete;
		scene &operator=(scene&&) = delete;
		scene(const scene&) = delete;
		scene(scene&&) = delete;
		scene();
		~scene();

		pulsar::ecs::registry	&registry();

		void	set_main_camera(pulsar::node *camera);
		pulsar::node	*get_main_camera();

		pulsar::skybox_material		&skybox_material();

		pulsar::node	create_node(const char *name = pulsar::DEFAULT_ENTITY_NAME);
		
		template <typename T, typename... Args>
		void	register_system(Args&&... args)
		{
			static_assert(std::is_base_of_v<pulsar::ecs::system, T>, "Invalid system-type");
			this->m_systems.push_back((pulsar::ecs::system*)(new T(args...)));
		}

		void	update(float delta_time);
	};
}
