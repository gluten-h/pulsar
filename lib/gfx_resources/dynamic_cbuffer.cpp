
#include "dynamic_cbuffer.h"
#include "exceptions/gfx_exception.h"


pulsar::dynamic_cbuffer::dynamic_cbuffer(pulsar::dcb::buffer *buffer, UINT slot)
{
	this->create_dcb(buffer);
	this->m_slot = slot;
}

void	pulsar::dynamic_cbuffer::create_dcb(pulsar::dcb::buffer *buffer)
{
	if (!buffer)
		return;
	this->mp_dcb = buffer;

	D3D11_BUFFER_DESC bd;
	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));

	bd.ByteWidth = (UINT)buffer->size();
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	sd.pSysMem = buffer->data();
	this->create_buffer(&bd, &sd);
}

bool	pulsar::dynamic_cbuffer::is_modified() const
{
	return (this->mp_dcb && this->mp_dcb->is_modified());
}

void	pulsar::dynamic_cbuffer::update()
{
	if (!this->mp_dcb)
		return;
	this->mp_dcb->set_updated();

	D3D11_MAPPED_SUBRESOURCE ms;
	GFX_ASSERT(pulsar::gfx::instance().device_context()->Map(this->mp_buffer, 0u, D3D11_MAP_WRITE_DISCARD, 0u, &ms));
	memcpy(ms.pData, this->mp_dcb->data(), this->mp_dcb->size());
	pulsar::gfx::instance().device_context()->Unmap(this->mp_buffer, 0u);
}

void	pulsar::dynamic_cbuffer::set(pulsar::dcb::buffer *buffer)
{
	this->destroy_buffer();
	this->create_dcb(buffer);
}

void	pulsar::dynamic_cbuffer::set_slot(UINT slot)
{
	this->m_slot = slot;
}
