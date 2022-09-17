#pragma once

#include "mesh.h"


namespace pulsar
{
	class quad : public pulsar::mesh
	{
	public:
		quad &operator=(const quad&) = delete;
		quad &operator=(quad&&) = delete;
		quad(const quad&) = delete;
		quad(quad&&) = delete;
		quad();
		~quad() = default;
	};
}
