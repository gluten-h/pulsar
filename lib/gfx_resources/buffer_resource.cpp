
#include "buffer_resource.h"
#include "exceptions/gfx_exception.h"


pulsar::buffer_resource::~buffer_resource()
{
	if (this->mp_buffer)
	{
		this->mp_buffer->Release();
		this->mp_buffer = NULL;
	}
}

void	pulsar::buffer_resource::create_buffer(const D3D11_BUFFER_DESC *bd, const D3D11_SUBRESOURCE_DATA *sd)
{
	GFX_ASSERT(pulsar::gfx::instance().device()->CreateBuffer(bd, sd, &this->mp_buffer));
}

void	pulsar::buffer_resource::destroy_buffer()
{
	if (this->mp_buffer)
	{
		this->mp_buffer->Release();
		this->mp_buffer = NULL;
	}
}

ID3D11Buffer	*pulsar::buffer_resource::buffer()
{
	return (this->mp_buffer);
}
