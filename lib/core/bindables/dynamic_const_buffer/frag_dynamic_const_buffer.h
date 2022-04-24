#pragma once

#include "dynamic_const_buffer.h"


namespace PULSAR
{
	class frag_dynamic_const_buffer : public PULSAR::dynamic_const_buffer
	{
	public:
		frag_dynamic_const_buffer &operator=(const frag_dynamic_const_buffer&) = delete;
		frag_dynamic_const_buffer &operator=(frag_dynamic_const_buffer&&) = delete;
		frag_dynamic_const_buffer(const frag_dynamic_const_buffer&) = delete;
		frag_dynamic_const_buffer(frag_dynamic_const_buffer&&) = delete;
		frag_dynamic_const_buffer(UINT slot = 0u) : PULSAR::dynamic_const_buffer(slot){ }
		frag_dynamic_const_buffer(PULSAR::dcb::buffer *dcb_buffer, UINT slot = 0u) : PULSAR::dynamic_const_buffer(dcb_buffer, slot){ }

		void	bind() const override;
		void	unbind() const override;
	};

	using frag_dcb = frag_dynamic_const_buffer;
}
