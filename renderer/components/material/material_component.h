#pragma once

#include "material.h"
#include "render_queue/types.h"
#include <array>


namespace pulsar
{
	struct material_component
	{
		std::array<pulsar::material*, pulsar::RENDERING_MODE::RENDERING_MODES_COUNT> rq_materials;

		material_component()
		{
			int i = -1;
			while (++i < pulsar::RENDERING_MODE::RENDERING_MODES_COUNT)
				this->rq_materials[i] = NULL;
		}
		~material_component() = default;
	};
}
