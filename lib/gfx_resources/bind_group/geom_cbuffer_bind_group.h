#pragma once

#include "cbuffer_bind_group.h"


namespace pulsar
{
	template <size_t SIZE>
	class geom_cbuffer_bind_group : public pulsar::cbuffer_bind_group<SIZE>
	{
	public:
		geom_cbuffer_bind_group() = default;
		geom_cbuffer_bind_group(const std::array<ID3D11Buffer*, SIZE> &data, UINT start_slot = 0u) : pulsar::cbuffer_bind_group<SIZE>(data, start_slot){ }
		~geom_cbuffer_bind_group() = default;a

		void	bind() const
		{
			pulsar::gfx::instance().device_context()->GSSetConstantBuffers(this->m_slot, SIZE, this->data);
		}

		void	unbind() const
		{
			ID3D11Buffer *null[SIZE] = { NULL };
			pulsar::gfx::instance().device_context()->GSSetConstantBuffers(this->m_slot, SIZE, null);
		}
	};
}
