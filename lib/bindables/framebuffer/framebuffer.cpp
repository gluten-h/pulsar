
#include "framebuffer.h"
#include "exceptions/gfx_exception.h"
#include "utils/math.h"


pulsar::framebuffer::framebuffer(HWND hwnd, BOOL windowed)
{
	this->create_feamebuffer(hwnd, windowed);
}

pulsar::framebuffer::~framebuffer()
{
	this->free();
}

void	pulsar::framebuffer::resize(UINT width, UINT height)
{
	if (this->mp_render_target)
	{
		this->mp_render_target->Release();
		this->mp_render_target = NULL;
	}

	ID3D11Texture2D *buffer;

	GFX_ASSERT(this->mp_swap_chain->ResizeBuffers(0u, width, height, DXGI_FORMAT_UNKNOWN, 0u));
	GFX_ASSERT(this->mp_swap_chain->GetBuffer(0u, __uuidof(ID3D11Texture2D), (void**)&buffer));
	GFX_ASSERT(pulsar::gfx::instance().device()->CreateRenderTargetView(buffer, NULL, &this->mp_render_target));

	buffer->Release();

	this->resize_linked(width, height);
}

void	pulsar::framebuffer::clear()
{
	float clear_color[4] = { 0.0f, 0.0f, 0.0f, 1.0 };
	pulsar::gfx::instance().device_context()->ClearRenderTargetView(this->mp_render_target, clear_color);
}

void	pulsar::framebuffer::present() const
{
	this->mp_swap_chain->Present(1u, 0u);
}

void	pulsar::framebuffer::bind(ID3D11DepthStencilView *ds_view) const
{
	pulsar::gfx::instance().device_context()->OMSetRenderTargets(1u, &this->mp_render_target, ds_view);
}

void	pulsar::framebuffer::unbind() const
{
	ID3D11RenderTargetView *null_ptr[1] = { NULL };
	pulsar::gfx::instance().device_context()->OMSetRenderTargets(1u, null_ptr, NULL);
}
