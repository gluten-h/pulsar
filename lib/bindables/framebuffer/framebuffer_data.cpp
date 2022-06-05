
#include "framebuffer/framebuffer.h"
#include "exceptions/gfx_exception.h"
#include "exceptions/win_exception.h"
#include "utils/math.h"


void	pulsar::framebuffer::create_feamebuffer(HWND hwnd, BOOL windowed)
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

	ID3D11Texture2D *buffer;

	GFX_ASSERT(pulsar::gfx::instance().idxgi_factory()->CreateSwapChain(pulsar::gfx::instance().device(), &scd, &this->mp_swap_chain));
	GFX_ASSERT(this->mp_swap_chain->GetBuffer(0u, __uuidof(ID3D11Texture2D), (void**)&buffer));
	GFX_ASSERT(pulsar::gfx::instance().device()->CreateRenderTargetView(buffer, NULL, &this->mp_render_target));

	buffer->Release();
}

void	pulsar::framebuffer::free()
{
	if (this->mp_swap_chain)
	{
		this->mp_swap_chain->SetFullscreenState(FALSE, NULL);
		this->mp_swap_chain->Release();
		this->mp_swap_chain = NULL;
	}
	if (this->mp_render_target)
	{
		this->mp_render_target->Release();
		this->mp_render_target = NULL;
	}
}

void	pulsar::framebuffer::set(HWND hwnd, BOOL windowed)
{
	this->free();
	this->create_feamebuffer(hwnd, windowed);
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
