#pragma once

#include "dynamic_cbuffer.h"


namespace pulsar
{
	class geom_dynamic_cbuffer : public pulsar::dynamic_cbuffer
	{
	public:
		geom_dynamic_cbuffer &operator=(const geom_dynamic_cbuffer&) = delete;
		geom_dynamic_cbuffer &operator=(geom_dynamic_cbuffer&&) = delete;
		geom_dynamic_cbuffer(const geom_dynamic_cbuffer&) = default;
		geom_dynamic_cbuffer(geom_dynamic_cbuffer&&) = default;
		geom_dynamic_cbuffer() = default;
		geom_dynamic_cbuffer(pulsar::dcb::buffer *dcb_buffer, UINT slot = 0u) : pulsar::dynamic_cbuffer(dcb_buffer, slot){ }
		~geom_dynamic_cbuffer() = default;

		void	bind() const;
		void	unbind() const;
	};
}
