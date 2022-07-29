
#include "framebuffer.h"
#include "exceptions/gfx_exception.h"
#include "exceptions/win_exception.h"


pulsar::framebuffer::framebuffer(HWND hwnd, BOOL windowed)
{
	this->create_framebuffer(hwnd, windowed);
}

pulsar::framebuffer::~framebuffer()
{
	this->destroy_framebuffer();
}

void	pulsar::framebuffer::create_framebuffer(HWND hwnd, BOOL windowed)
{
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
	scd.BufferCount = 2u;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.SampleDesc.Count = 1u;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = hwnd;
	scd.Windowed = windowed;
	scd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	GFX_ASSERT(pulsar::gfx::instance().idxgi_factory()->CreateSwapChain(pulsar::gfx::instance().device(), &scd, &this->mp_swap_chain));
	GFX_ASSERT(this->mp_swap_chain->GetBuffer(0u, __uuidof(ID3D11Texture2D), (void**)&this->mp_texture));
	GFX_ASSERT(pulsar::gfx::instance().device()->CreateRenderTargetView(this->mp_texture, NULL, &this->mp_rtv));
}

void	pulsar::framebuffer::destroy_framebuffer()
{
	if (this->mp_swap_chain)
	{
		this->mp_swap_chain->SetFullscreenState(FALSE, NULL);
		this->mp_swap_chain->Release();
		this->mp_swap_chain = NULL;
	}
	if (this->mp_rtv)
	{
		this->mp_rtv->Release();
		this->mp_rtv = NULL;
	}
}

void	pulsar::framebuffer::set(HWND hwnd, BOOL windowed)
{
	this->destroy_texture();
	this->destroy_framebuffer();
	this->create_framebuffer(hwnd, windowed);
}

XMUINT2		pulsar::framebuffer::size() const
{
	if (!this->mp_swap_chain)
		return (XMUINT2(0u, 0u));

	DXGI_SWAP_CHAIN_DESC swd;
	RECT rect;

	this->mp_swap_chain->GetDesc(&swd);
	if (!GetClientRect(swd.OutputWindow, &rect))
		THROW_LAST_WIN_EXC();

	return (XMUINT2(rect.right - rect.left, rect.bottom - rect.top));
}

void	pulsar::framebuffer::resize_resource(UINT width, UINT height)
{
	this->destroy_texture();
	if (this->mp_rtv)
	{
		this->mp_rtv->Release();
		this->mp_rtv = NULL;
	}

	GFX_ASSERT(this->mp_swap_chain->ResizeBuffers(0u, width, height, DXGI_FORMAT_UNKNOWN, 0u));
	GFX_ASSERT(this->mp_swap_chain->GetBuffer(0u, __uuidof(ID3D11Texture2D), (void**)&this->mp_texture));
	GFX_ASSERT(pulsar::gfx::instance().device()->CreateRenderTargetView(this->mp_texture, NULL, &this->mp_rtv));
}

void	pulsar::framebuffer::clear()
{
	float clear_color[4] = { 0.0f, 0.0f, 0.0f, 1.0 };
	pulsar::gfx::instance().device_context()->ClearRenderTargetView(this->mp_rtv, clear_color);
}

void	pulsar::framebuffer::present() const
{
	this->mp_swap_chain->Present(1u, 0u);
}

void	pulsar::framebuffer::bind(ID3D11DepthStencilView *dsv) const
{
	pulsar::gfx::instance().device_context()->OMSetRenderTargets(1u, &this->mp_rtv, dsv);
}

void	pulsar::framebuffer::unbind() const
{
	ID3D11RenderTargetView *null_ptr[1] = { NULL };
	pulsar::gfx::instance().device_context()->OMSetRenderTargets(1u, null_ptr, NULL);
}
