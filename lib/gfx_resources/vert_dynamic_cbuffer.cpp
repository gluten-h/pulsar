
#include "vert_dynamic_cbuffer.h"


void	pulsar::vert_dynamic_cbuffer::bind() const
{
	pulsar::gfx::instance().device_context()->VSSetConstantBuffers(this->m_slot, 1u, &this->mp_buffer);
}

void	pulsar::vert_dynamic_cbuffer::unbind() const
{
	ID3D11Buffer *null[1] = { NULL };
	pulsar::gfx::instance().device_context()->VSSetConstantBuffers(this->m_slot, 1u, null);
}
