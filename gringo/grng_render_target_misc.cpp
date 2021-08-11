
#include "grng_render_target.h"


void		grng_render_target::clear()
{
	this->device_context->ClearRenderTargetView(this->back_buffer, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
}

void		grng_render_target::present()
{
	this->swap_chain->Present(1u, 0u);
}
