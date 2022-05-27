#pragma once

#include "ecs/system.h"


namespace pulsar
{
	class render_system : public pulsar::ecs::system
	{
	public:
		render_system() = delete;
		render_system(pulsar::ecs::registry *registry);
		~render_system() = default;

		void	execute(float delta_time) override;
	};
}
