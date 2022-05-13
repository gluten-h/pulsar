#pragma once

#include "ecs/registry.h"
#include "scene/scene.h"
#include <cassert>
#include <utility>


namespace PULSAR
{
	class node
	{
	private:
		PULSAR::ecs::entity m_id = PULSAR::ecs::null;
		PULSAR::scene *mp_scene = NULL;

	public:
		node() = default;
		node(PULSAR::ecs::entity id, PULSAR::scene *p_scene);
		~node() = default;

		void	destroy();
		bool	is_valid() const;
		operator bool() const;

		template <typename T>
		bool	has_component() const
		{
			return (this->mp_scene->m_registry.has<T>(this->m_id));
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
