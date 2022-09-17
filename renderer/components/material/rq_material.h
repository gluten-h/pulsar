#pragma once

#include "material.h"
#include "config/config.h"


namespace pulsar
{
	struct rq_material
	{
		pulsar::VIEWPORT_RQ_MODE mode = pulsar::VIEWPORT_RQ_MODE::VIEWPORT_RQ_OPAQUE;
		pulsar::material *material = NULL;

		rq_material() = default;
		rq_material(pulsar::material *p_material, pulsar::VIEWPORT_RQ_MODE mode = pulsar::VIEWPORT_RQ_MODE::VIEWPORT_RQ_OPAQUE)
		{
			this->mode = mode;
			this->material = p_material;
		}
		~rq_material() = default;
	};
}
