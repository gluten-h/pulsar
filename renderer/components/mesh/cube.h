#pragma once

#include "mesh.h"


namespace pulsar
{
	class cube : public pulsar::mesh
	{
	public:
		cube &operator=(const cube&) = delete;
		cube &operator=(cube&&) = delete;
		cube(const cube&) = delete;
		cube(cube&&) = delete;
		cube();
		~cube() = default;
	};
}
