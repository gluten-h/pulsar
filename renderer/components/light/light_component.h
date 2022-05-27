#pragma once

#include "point_light.h"
#include "dir_light.h"


namespace pulsar
{
	struct light_component
	{
		pulsar::light *light = NULL;

		light_component() = default;
		light_component(pulsar::light *light)
		{
			this->light = light;
		}
		~light_component() = default;
	};
}
