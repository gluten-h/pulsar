#pragma once

#include "dynamic_const_buffer.h"


namespace pulsar
{
	class vert_dynamic_const_buffer : public pulsar::dynamic_const_buffer
	{
	public:
		vert_dynamic_const_buffer &operator=(const vert_dynamic_const_buffer&) = delete;
		vert_dynamic_const_buffer &operator=(vert_dynamic_const_buffer&&) = delete;
		vert_dynamic_const_buffer(const vert_dynamic_const_buffer&) = default;
		vert_dynamic_const_buffer(vert_dynamic_const_buffer&&) = default;
		vert_dynamic_const_buffer(UINT slot = 0u) : pulsar::dynamic_const_buffer(slot){ }
		vert_dynamic_const_buffer(pulsar::dcb::buffer *dcb_buffer, UINT slot = 0u) : pulsar::dynamic_const_buffer(dcb_buffer, slot){ }

		void	bind() const;
		void	unbind() const;
	};

	using vert_dcb = vert_dynamic_const_buffer;
}
