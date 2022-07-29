#pragma once

#include "dynamic_cbuffer.h"


namespace pulsar
{
	class frag_dynamic_cbuffer : public pulsar::dynamic_cbuffer
	{
	public:
		frag_dynamic_cbuffer &operator=(const frag_dynamic_cbuffer&) = delete;
		frag_dynamic_cbuffer &operator=(frag_dynamic_cbuffer&&) = delete;
		frag_dynamic_cbuffer(const frag_dynamic_cbuffer&) = default;
		frag_dynamic_cbuffer(frag_dynamic_cbuffer&&) = default;
		frag_dynamic_cbuffer() = default;
		frag_dynamic_cbuffer(pulsar::dcb::buffer *dcb_buffer, UINT slot = 0u) : pulsar::dynamic_cbuffer(dcb_buffer, slot){ }
		~frag_dynamic_cbuffer() = default;

		void	bind() const;
		void	unbind() const;
	};
}
