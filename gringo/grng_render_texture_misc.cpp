
#include "grng_render_texture.h"


void		grng_render_texture::clear()
{
	this->device_context->ClearRenderTargetView(this->texture_rtv, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
}

void		grng_render_texture::bind() const
{
	switch (this->mode)
	{
		case GRNG_BIND_MODE::SRV:
		{
			this->device_context->PSSetShaderResources(this->slot, 1u, &this->texture_srv);
			break;
		}
		case GRNG_BIND_MODE::RTV:
		{
			this->device_context->OMSetRenderTargets(1u, &this->texture_rtv, this->ds_view);
			break;
		}
	}

	GRNG_BINDABLE::add_unbind(*this);
}

void		grng_render_texture::unbind() const
{
	switch (this->mode)
	{
		case GRNG_BIND_MODE::SRV:
		{
			this->device_context->PSSetShaderResources(this->slot, 0u, NULL);
			break;
		}
		case GRNG_BIND_MODE::RTV:
		{
			this->device_context->OMSetRenderTargets(0u, NULL, NULL);
			break;
		}
	}
	this->ds_view = NULL;
}
