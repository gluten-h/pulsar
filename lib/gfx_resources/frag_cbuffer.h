#pragma once

#include "cbuffer.h"


namespace pulsar
{
	template <typename T>
	class frag_cbuffer : public pulsar::cbuffer<T>
	{
	public:
		frag_cbuffer<T> &operator=(const frag_cbuffer<T>&) = delete;
		frag_cbuffer<T> &operator=(frag_cbuffer<T>&&) = delete;
		frag_cbuffer(const frag_cbuffer<T>&) = delete;
		frag_cbuffer(frag_cbuffer<T>&&) = delete;
		frag_cbuffer() = default;
		frag_cbuffer(const T *data, pulsar::CBUFFER_TYPE type = pulsar::CBUFFER_TYPE::DYNAMIC, UINT slot = 0u) : pulsar::cbuffer<T>(data, type, slot){ }
		~frag_cbuffer() = default;

		void	bind()
		{
			pulsar::gfx::instance().device_context()->PSSetConstantBuffers(this->m_slot, 1u, &this->mp_buffer);
		}

		void	unbind()
		{
			ID3D11Buffer *null_ptr[1] = { NULL };
			pulsar::gfx::instance().device_context()->PSSetConstantBuffers(this->m_slot, 1u, null_ptr);
		}
	};
}
