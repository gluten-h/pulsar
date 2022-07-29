#pragma once

#include "cbuffer.h"


namespace pulsar
{
	template <typename T>
	class vert_cbuffer : public pulsar::cbuffer<T>
	{
	public:
		vert_cbuffer<T> &operator=(const vert_cbuffer<T>&) = delete;
		vert_cbuffer<T> &operator=(vert_cbuffer<T>&&) = delete;
		vert_cbuffer(const vert_cbuffer<T>&) = delete;
		vert_cbuffer(vert_cbuffer<T>&&) = delete;
		vert_cbuffer() = default;
		vert_cbuffer(const T *data, pulsar::CBUFFER_TYPE type = pulsar::CBUFFER_TYPE::DYNAMIC, UINT slot = 0u) : pulsar::cbuffer<T>(data, type, slot){ }
		~vert_cbuffer() = default;

		void	bind()
		{
			pulsar::gfx::instance().device_context()->VSSetConstantBuffers(this->m_slot, 1u, &this->mp_buffer);
		}

		void	unbind()
		{
			ID3D11Buffer *null_ptr[1] = { NULL };
			pulsar::gfx::instance().device_context()->VSSetConstantBuffers(this->m_slot, 0u, null_ptr);
		}
	};
}
