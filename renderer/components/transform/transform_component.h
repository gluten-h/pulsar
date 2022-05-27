#pragma once

#include "transform.h"


namespace pulsar
{
	struct transform_component
	{
		pulsar::transform transform;

		transform_component() = default;
		transform_component(const pulsar::transform &transform)
		{
			this->transform = transform;
		}
		~transform_component() = default;
	};
}
