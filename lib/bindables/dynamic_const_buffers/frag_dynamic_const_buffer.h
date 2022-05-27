#pragma once

#include "dynamic_const_buffer.h"


namespace pulsar
{
	class frag_dynamic_const_buffer : public pulsar::dynamic_const_buffer
	{
	public:
		frag_dynamic_const_buffer &operator=(const frag_dynamic_const_buffer&) = delete;
		frag_dynamic_const_buffer &operator=(frag_dynamic_const_buffer&&) = delete;
		frag_dynamic_const_buffer(const frag_dynamic_const_buffer&) = default;
		frag_dynamic_const_buffer(frag_dynamic_const_buffer&&) = default;
		frag_dynamic_const_buffer(UINT slot = 0u) : pulsar::dynamic_const_buffer(slot){ }
		frag_dynamic_const_buffer(pulsar::dcb::buffer *dcb_buffer, UINT slot = 0u) : pulsar::dynamic_const_buffer(dcb_buffer, slot){ }

		void	bind() const;
		void	unbind() const;
	};

	using frag_dcb = frag_dynamic_const_buffer;
}
