#pragma once

#include "types.h"
#include <cstddef>


namespace pulsar
{
	namespace ecs
	{
		class system
		{
		public:
			system() = default;
			virtual ~system() = default;

			virtual void	execute(pulsar::ecs::registry &registry, float delta_time) = 0;
		};
	}
}
