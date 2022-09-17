#pragma once

#include "mask/mask.h"
#include <string>
#include "ecs/ecs.h"
#include "config/config.h"
#include "metadata/metadata_component.h"


namespace pulsar
{
	struct metadata_component
	{
		std::string name = std::string(pulsar::DEFAULT_ENTITY_NAME);
		pulsar::mask mask;

		metadata_component() = default;
		metadata_component(const char *name)
		{
			this->name = name;
		}
		~metadata_component() = default;

		void	on_construct(pulsar::ecs::registry &registry, pulsar::ecs::entity entity)
		{
			this->mask.viewport = pulsar::DEFAULT_ENTITY_VIEWPORT_MASK;
			this->mask.shadows = pulsar::DEFAULT_ENTITY_SHADOWS_MASK;
		}
	};
}
