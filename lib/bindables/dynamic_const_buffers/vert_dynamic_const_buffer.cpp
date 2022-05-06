
#include "vert_dynamic_const_buffer.h"


void	PULSAR::vert_dynamic_const_buffer::bind() const
{
	PULSAR::gfx::get().device_context()->VSSetConstantBuffers(this->m_slot, 1u, &this->mp_buffer);
}

void	PULSAR::vert_dynamic_const_buffer::unbind() const
{
	static ID3D11Buffer *null_ptr[1] = { NULL };
	PULSAR::gfx::get().device_context()->VSSetConstantBuffers(this->m_slot, 0u, null_ptr);
}
