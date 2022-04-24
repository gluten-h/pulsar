
#include "framebuffer.h"


PULSAR::framebuffer::framebuffer(HWND hwnd, BOOL windowed)
{
	this->create_feamebuffer(hwnd, windowed);
}

PULSAR::framebuffer::~framebuffer()
{
	this->free();
}

void	PULSAR::framebuffer::clear()
{
	PULSAR::gfx::get().device_context()->ClearRenderTargetView(this->mp_render_target, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
}

void	PULSAR::framebuffer::present()
{
	this->mp_swap_chain->Present(1u, 0u);
}

void	PULSAR::framebuffer::bind() const
{
	PULSAR::gfx::get().device_context()->OMSetRenderTargets(1u, &this->mp_render_target, this->mp_ds_view);
}

void	PULSAR::framebuffer::unbind() const
{
	static ID3D11RenderTargetView *null_ptr[1] = { NULL };
	PULSAR::gfx::get().device_context()->OMSetRenderTargets(1u, null_ptr, NULL);
	this->mp_ds_view = NULL;
}
