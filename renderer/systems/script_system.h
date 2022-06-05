#pragma once

#include "ecs/system.h"


namespace pulsar
{
	class script_system : public pulsar::ecs::system
	{
	public:
		script_system() = delete;
		script_system(pulsar::ecs::registry *registry);
		~script_system() = default;

		void	execute(float delta_time) override;
	};
}
