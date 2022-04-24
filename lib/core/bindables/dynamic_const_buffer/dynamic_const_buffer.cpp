
#include "dynamic_const_buffer.h"


PULSAR::dynamic_const_buffer::dynamic_const_buffer(UINT slot = 0u)
{
	this->m_slot = slot;
}

PULSAR::dynamic_const_buffer::dynamic_const_buffer(PULSAR::dcb::buffer *dcb_buffer, UINT slot = 0u)
{
	this->create_buffer(dcb_buffer);
	this->set_slot(slot);
}

PULSAR::dynamic_const_buffer::~dynamic_const_buffer()
{
	this->free();
}

bool	PULSAR::dynamic_const_buffer::is_modified() const noexcept
{
	return (this->mp_dcb_buffer && this->mp_dcb_buffer->is_modified());
}

void	PULSAR::dynamic_const_buffer::update()
{
	if (!this->mp_dcb_buffer)
		return;

	D3D11_MAPPED_SUBRESOURCE ms;
	GFX_ASSERT(PULSAR::gfx::get().device_context()->Map(this->mp_buffer, 0u, D3D11_MAP_WRITE_DISCARD, 0u, &ms));
	memcpy(ms.pData, this->mp_dcb_buffer->data(), this->mp_dcb_buffer->size());
	PULSAR::gfx::get().device_context()->Unmap(this->mp_buffer, 0u);

	this->mp_dcb_buffer->set_updated();
}

void	PULSAR::dynamic_const_buffer::set_dcb_buffer(PULSAR::dcb::buffer *dcb_buffer)
{
	this->free();
	this->create_buffer(dcb_buffer);
}

void	PULSAR::dynamic_const_buffer::set_slot(UINT slot)
{
	this->m_slot = slot;
}
