#pragma once

#include "ecs/system.h"


namespace pulsar
{
	class viewport_render_system : public pulsar::ecs::system
	{
	public:
		viewport_render_system() = default;
		~viewport_render_system() = default;

		void	execute(pulsar::ecs::registry &registry, float delta_time) override;
	};
}
