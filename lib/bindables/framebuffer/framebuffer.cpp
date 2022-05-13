
#include "framebuffer.h"
#include "exceptions/gfx_exception.h"
#include "utils/math.h"


PULSAR::framebuffer::framebuffer(HWND hwnd, BOOL windowed)
{
	this->create_feamebuffer(hwnd, windowed);
}

PULSAR::framebuffer::~framebuffer()
{
	this->free();
}

void	PULSAR::framebuffer::resize(UINT width, UINT height)
{
	if (this->mp_render_target)
	{
		this->mp_render_target->Release();
		this->mp_render_target = NULL;
	}

	ID3D11Texture2D *buffer;

	GFX_ASSERT(this->mp_swap_chain->ResizeBuffers(0u, width, height, DXGI_FORMAT_UNKNOWN, 0u));
	GFX_ASSERT(this->mp_swap_chain->GetBuffer(0u, __uuidof(ID3D11Texture2D), (void**)&buffer));
	GFX_ASSERT(PULSAR::gfx::get().device()->CreateRenderTargetView(buffer, NULL, &this->mp_render_target));

	buffer->Release();

	this->resize_linked(width, height);
}

void	PULSAR::framebuffer::clear()
{
	float clear_color[4] = { 0.0f, 0.0f, 0.0f, 1.0 };
	PULSAR::gfx::get().device_context()->ClearRenderTargetView(this->mp_render_target, clear_color);
}

void	PULSAR::framebuffer::present() const
{
	this->mp_swap_chain->Present(1u, 0u);
}

void	PULSAR::framebuffer::bind() const
{
	PULSAR::gfx::get().device_context()->OMSetRenderTargets(1u, &this->mp_render_target, this->mp_ds_view);
}

void	PULSAR::framebuffer::unbind() const
{
	ID3D11RenderTargetView *null_ptr[1] = { NULL };
	PULSAR::gfx::get().device_context()->OMSetRenderTargets(1u, null_ptr, NULL);
	this->mp_ds_view = NULL;
}
