
#include "render_target.h"


void		PULSAR::RENDER_TARGET::clear()
{
	this->device_context->ClearRenderTargetView(this->back_buffer, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
}

void		PULSAR::RENDER_TARGET::present()
{
	this->swap_chain->Present(1u, 0u);
}
