
#include "frag_dynamic_const_buffer.h"


void	pulsar::frag_dynamic_const_buffer::bind() const
{
	pulsar::gfx::instance().device_context()->PSSetConstantBuffers(this->m_slot, 1u, &this->mp_buffer);
}

void	pulsar::frag_dynamic_const_buffer::unbind() const
{
	ID3D11Buffer *null_ptr[1] = { NULL };
	pulsar::gfx::instance().device_context()->PSSetConstantBuffers(this->m_slot, 0u, null_ptr);
}
