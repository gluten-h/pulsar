#pragma once

#include "mesh.h"


namespace pulsar
{
	struct mesh_component
	{
		pulsar::mesh *mesh = NULL;

		mesh_component() = default;
		mesh_component(pulsar::mesh *mesh)
		{
			this->mesh = mesh;
		}
		~mesh_component() = default;
	};
}
