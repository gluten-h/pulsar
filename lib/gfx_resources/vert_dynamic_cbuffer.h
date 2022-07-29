#pragma once

#include "dynamic_cbuffer.h"


namespace pulsar
{
	class vert_dynamic_cbuffer : public pulsar::dynamic_cbuffer
	{
	public:
		vert_dynamic_cbuffer &operator=(const vert_dynamic_cbuffer&) = delete;
		vert_dynamic_cbuffer &operator=(vert_dynamic_cbuffer&&) = delete;
		vert_dynamic_cbuffer(const vert_dynamic_cbuffer&) = default;
		vert_dynamic_cbuffer(vert_dynamic_cbuffer&&) = default;
		vert_dynamic_cbuffer() = default;
		vert_dynamic_cbuffer(pulsar::dcb::buffer *dcb_buffer, UINT slot = 0u) : pulsar::dynamic_cbuffer(dcb_buffer, slot){ }
		~vert_dynamic_cbuffer() = default;

		void	bind() const;
		void	unbind() const;
	};
}
