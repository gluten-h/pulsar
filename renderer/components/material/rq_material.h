#pragma once

#include "material.h"
#include "render_queue/types.h"


namespace pulsar
{
	struct rq_material
	{
		pulsar::RQ_MODE mode = pulsar::RQ_MODE::RQ_OPAQUE;
		pulsar::material *material = NULL;

		rq_material() = default;
		rq_material(pulsar::material *p_material, pulsar::RQ_MODE mode = pulsar::RQ_MODE::RQ_OPAQUE)
		{
			this->mode = mode;
			this->material = p_material;
		}
		~rq_material() = default;
	};
}
