
#include "grng_render_target.h"


void		grng_render_target::clear()
{
	this->device_context->ClearRenderTargetView(this->back_buffer, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
}

void		grng_render_target::present()
{
	this->swap_chain->Present(1u, 0u);
}

void		grng_render_target::bind() const
{
	this->device_context->OMSetRenderTargets(1u, &this->back_buffer, NULL);
}

void		grng_render_target::bind(ID3D11DepthStencilView *ds_view) const
{
	this->device_context->OMSetRenderTargets(1u, &this->back_buffer, ds_view);
}
