#pragma once

#include "const_buffer.h"


namespace PULSAR
{
	template <typename T>
	class frag_const_buffer : public PULSAR::const_buffer<T>
	{
	public:
		frag_const_buffer<T> &operator=(const frag_const_buffer<T>&) = delete;
		frag_const_buffer<T> &operator=(frag_const_buffer<T>&&) = delete;
		frag_const_buffer(const frag_const_buffer<T>&) = delete;
		frag_const_buffer(frag_const_buffer<T>&&) = delete;
		frag_const_buffer(UINT slot = 0u) : PULSAR::const_buffer<T>(slot)
		{
		}
		frag_const_buffer(const T &data, UINT slot = 0u) : PULSAR::const_buffer<T>(data, slot)
		{
		}

		void	bind() const override
		{
			PULSAR::gfx::get().device_context()->PSSetConstantBuffers(this->m_slot, 1u, &this->mp_buffer);
		}
		void	unbind() const override
		{
			ID3D11Buffer *nullPtr[1] = { NULL };
			PULSAR::gfx::get().device_context()->PSSetConstantBuffers(this->m_slot, 1u, nullPtr);
		}
	};
}
