#pragma once

#include "cbuffer.h"


namespace pulsar
{
	template <typename T>
	class geom_cbuffer : public pulsar::cbuffer<T>
	{
	public:
		geom_cbuffer<T> &operator=(const geom_cbuffer<T>&) = delete;
		geom_cbuffer<T> &operator=(geom_cbuffer<T>&&) = delete;
		geom_cbuffer(const geom_cbuffer<T>&) = delete;
		geom_cbuffer(geom_cbuffer<T>&&) = delete;
		geom_cbuffer() = default;
		geom_cbuffer(const T *data, pulsar::CBUFFER_TYPE type = pulsar::CBUFFER_TYPE::DYNAMIC, UINT slot = 0u) : pulsar::cbuffer<T>(data, type, slot){ }
		~geom_cbuffer() = default;

		void	bind()
		{
			pulsar::gfx::instance().device_context()->GSSetConstantBuffers(this->m_slot, 1u, &this->mp_buffer);
		}

		void	unbind()
		{
			ID3D11Buffer *null[1] = { NULL };
			pulsar::gfx::instance().device_context()->GSSetConstantBuffers(this->m_slot, 1u, null);
		}
	};
}
