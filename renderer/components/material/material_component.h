#pragma once

#include "material.h"
#include "render_queue/types.h"
#include <array>


namespace PULSAR
{
	struct material_component
	{
		std::array<PULSAR::material*, PULSAR::RENDERING_MODE::RENDERING_MODES_COUNT> rq_materials;

		material_component()
		{
			int i = -1;
			while (++i < PULSAR::RENDERING_MODE::RENDERING_MODES_COUNT)
				this->rq_materials[i] = NULL;
		}
		~material_component() = default;
	};
}
