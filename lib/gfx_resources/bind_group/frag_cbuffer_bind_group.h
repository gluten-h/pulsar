#pragma once

#include "cbuffer_bind_group.h"


namespace pulsar
{
	template <size_t SIZE>
	class frag_cbuffer_bind_group : public pulsar::cbuffer_bind_group<SIZE>
	{
	public:
		frag_cbuffer_bind_group() = default;
		frag_cbuffer_bind_group(const std::array<ID3D11Buffer*, SIZE> &data, UINT start_slot = 0u) : pulsar::cbuffer_bind_group<SIZE>(data, start_slot){ }
		~frag_cbuffer_bind_group() = default;

		void	bind() const
		{
			pulsar::gfx::instance().device_context()->PSSetConstantBuffers(this->m_slot, SIZE, this->data);
		}

		void	unbind() const
		{
			ID3D11Buffer *null[SIZE] = { NULL };
			pulsar::gfx::instance().device_context()->PSSetConstantBuffers(this->m_slot, SIZE, null);
		}
	};
}
