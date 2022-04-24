#pragma once

#include "const_buffer.h"


namespace PULSAR
{
	template <typename T>
	class vert_const_buffer : public PULSAR::const_buffer<T>
	{
	public:
		vert_const_buffer<T> &operator=(const vert_const_buffer<T>&) = delete;
		vert_const_buffer<T> &operator=(vert_const_buffer<T>&&) = delete;
		vert_const_buffer(const vert_const_buffer<T>&) = delete;
		vert_const_buffer(vert_const_buffer<T>&&) = delete;
		vert_const_buffer(UINT slot = 0u) : PULSAR::const_buffer<T>(slot){ }
		vert_const_buffer(const T &data, UINT slot = 0u) : PULSAR::const_buffer<T>(data, slot){ }

		void	bind() const override
		{
			PULSAR::gfx::get().device_context()->VSSetConstantBuffers(this->m_slot, 1u, &this->mp_buffer);
			BINDABLE::add_unbind(*this);
		}
		void	unbind() const override
		{
			static ID3D11Buffer *nullPtr[1] = { NULL };
			PULSAR::gfx::get().device_context()->VSSetConstantBuffers(this->m_slot, 0u, nullPtr);
		}
	};
}
