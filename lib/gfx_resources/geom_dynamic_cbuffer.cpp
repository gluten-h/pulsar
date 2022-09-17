
#include "geom_dynamic_cbuffer.h"


void	pulsar::geom_dynamic_cbuffer::bind() const
{
	pulsar::gfx::instance().device_context()->GSSetConstantBuffers(this->m_slot, 1u, &this->mp_buffer);
}

void	pulsar::geom_dynamic_cbuffer::unbind() const
{
	ID3D11Buffer *null[1] = { NULL };
	pulsar::gfx::instance().device_context()->GSSetConstantBuffers(this->m_slot, 1u, null);
}
