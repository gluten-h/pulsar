#pragma once

#include "rq_material.h"
#include <vector>
#include <type_traits>


namespace pulsar
{
	struct material_component
	{
		std::vector<pulsar::rq_material> rq_materials;

		material_component() = default;

		template<typename... T, typename = std::enable_if_t<std::conjunction_v<std::is_same<T, pulsar::rq_material>...>>>
		material_component(T... rq_materials)
		{
			this->rq_materials = { { rq_materials... } };
		}

		~material_component() = default;
	};
}
