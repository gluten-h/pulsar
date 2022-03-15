
#include "render_texture.h"


void		PULSAR::RENDER_TEXTURE::clear()
{
	this->device_context->ClearRenderTargetView(this->texture_rtv, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
}

void		PULSAR::RENDER_TEXTURE::bind() const
{
	switch (this->mode)
	{
		case PULSAR::BIND_MODE::SRV:
		{
			this->device_context->PSSetShaderResources(this->slot, 1u, &this->texture_srv);
			break;
		}
		case PULSAR::BIND_MODE::RTV:
		{
			this->device_context->OMSetRenderTargets(1u, &this->texture_rtv, this->ds_view);
			break;
		}
	}

	PULSAR::BINDABLE::add_unbind(*this);
}

void		PULSAR::RENDER_TEXTURE::unbind() const
{
	switch (this->mode)
	{
		case PULSAR::BIND_MODE::SRV:
		{
			static ID3D11ShaderResourceView *null_ptr[1] = { NULL };
			this->device_context->PSSetShaderResources(this->slot, 1u, null_ptr);
			break;
		}
		case PULSAR::BIND_MODE::RTV:
		{
			static ID3D11RenderTargetView *null_ptr[1] = { NULL };
			this->device_context->OMSetRenderTargets(1u, null_ptr, NULL);
			break;
		}
	}
	this->ds_view = NULL;
}
