
#include "dynamic_const_buffer.h"
#include "exceptions/gfx_exception.h"


void	PULSAR::dynamic_const_buffer::create_buffer(PULSAR::dcb::buffer *dcb_buffer)
{
	if (!dcb_buffer)
		return;
	this->mp_dcb_buffer = dcb_buffer;

	D3D11_BUFFER_DESC bd;
	bd.ByteWidth = (UINT)dcb_buffer->size();
	bd.StructureByteStride = 0u;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0u;

	D3D11_SUBRESOURCE_DATA sd;
	sd.pSysMem = dcb_buffer->data();
	sd.SysMemPitch = 0u;
	sd.SysMemSlicePitch = 0u;
	GFX_ASSERT(PULSAR::gfx::get().device()->CreateBuffer(&bd, &sd, &this->mp_buffer));
}

void	PULSAR::dynamic_const_buffer::free()
{
	if (this->mp_buffer)
	{
		this->mp_buffer->Release();
		this->mp_buffer = NULL;
	}
}
