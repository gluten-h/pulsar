
#include "vert_dynamic_const_buffer.h"


void	pulsar::vert_dynamic_const_buffer::bind() const
{
	pulsar::gfx::instance().device_context()->VSSetConstantBuffers(this->m_slot, 1u, &this->mp_buffer);
}

void	pulsar::vert_dynamic_const_buffer::unbind() const
{
	ID3D11Buffer *null_ptr[1] = { NULL };
	pulsar::gfx::instance().device_context()->VSSetConstantBuffers(this->m_slot, 0u, null_ptr);
}
