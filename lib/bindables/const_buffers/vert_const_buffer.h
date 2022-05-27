#pragma once

#include "const_buffer.h"


namespace pulsar
{
	template <typename T>
	class vert_const_buffer : public pulsar::const_buffer<T>
	{
	public:
		vert_const_buffer<T> &operator=(const vert_const_buffer<T>&) = delete;
		vert_const_buffer<T> &operator=(vert_const_buffer<T>&&) = delete;
		vert_const_buffer(const vert_const_buffer<T>&) = delete;
		vert_const_buffer(vert_const_buffer<T>&&) = delete;
		vert_const_buffer() = default;
		vert_const_buffer(UINT slot) : pulsar::const_buffer<T>(slot){ }
		vert_const_buffer(const T &data, UINT slot = 0u) : pulsar::const_buffer<T>(data, slot){ }
		~vert_const_buffer() = default;

		void	bind() const
		{
			pulsar::gfx::instance().device_context()->VSSetConstantBuffers(this->m_slot, 1u, &this->mp_buffer);
		}
		void	unbind() const
		{
			ID3D11Buffer *nullPtr[1] = { NULL };
			pulsar::gfx::instance().device_context()->VSSetConstantBuffers(this->m_slot, 0u, nullPtr);
		}
	};
}
