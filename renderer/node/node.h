#pragma once

#include "scene/scene.h"
#include <cassert>
#include <utility>


namespace pulsar
{
	class node
	{
	private:
		pulsar::ecs::entity m_id = pulsar::ecs::null;
		pulsar::scene *mp_scene = NULL;

	public:
		node() = default;
		node(pulsar::ecs::entity id, pulsar::scene *scene);
		~node() = default;

		void	destroy();
		bool	is_valid() const;

		template <typename T>
		bool	has_component() const
		{
			return (this->mp_scene->m_registry.any_of<T>(this->m_id));
		}

		template <typename T>
		T	&get_component()
		{
			assert(("Node doesn't have component", this->has_component<T>()));
			return (this->mp_scene->m_registry.get<T>(this->m_id));
		}

		template <typename T, typename... Args>
		T	&add_component(Args&&... args)
		{
			assert(("Node already has component", !this->has_component<T>()));
			return (this->mp_scene->m_registry.emplace<T>(this->m_id, std::forward<Args>(args)...));
		}

		template <typename T>
		void	remove_component()
		{
			assert(("Node doesn't have component", this->has_component<T>()));
			this->mp_scene->m_registry.erase<T>(this->m_id);
		}
	};
}
