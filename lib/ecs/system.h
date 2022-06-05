#pragma once

#include "types.h"
#include <cstddef>


namespace pulsar
{
	namespace ecs
	{
		class system
		{
		protected:
			pulsar::ecs::registry *mp_registry = NULL;

			system(pulsar::ecs::registry *registry)
			{
				this->mp_registry = registry;
			}
		
		public:
			system() = delete;
			virtual ~system() = default;

			virtual void	execute(float delta_time) = 0;
		};
	}
}
