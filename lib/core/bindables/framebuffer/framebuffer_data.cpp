
#include "framebuffer/framebuffer.h"


void	PULSAR::framebuffer::create_feamebuffer(HWND hwnd, BOOL windowed)
{
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
	scd.BufferCount = 1u;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.SampleDesc.Count = 1u;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = hwnd;
	scd.Windowed = windowed;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	GFX_ASSERT(PULSAR::gfx::get().idxgi_factory()->CreateSwapChain(PULSAR::gfx::get().device(), &scd, &this->mp_swap_chain));
	GFX_ASSERT(this->mp_swap_chain->GetBuffer(0u, __uuidof(ID3D11Texture2D), (LPVOID*)&this->mp_texture));
	GFX_ASSERT(PULSAR::gfx::get().device()->CreateRenderTargetView(this->mp_texture, NULL, &this->mp_render_target));
}

void	PULSAR::framebuffer::free()
{
	if (this->mp_swap_chain)
	{
		this->mp_swap_chain->Release();
		this->mp_swap_chain = NULL;
	}
	if (this->mp_texture)
	{
		this->mp_texture->Release();
		this->mp_texture = NULL;
	}
	if (this->mp_render_target)
	{
		this->mp_render_target->Release();
		this->mp_render_target = NULL;
	}
}

void	PULSAR::framebuffer::set(HWND hwnd, BOOL windowed)
{
	this->free();
	this->create_feamebuffer(hwnd, windowed);
}

ID3D11DepthStencilView	*&PULSAR::framebuffer::ds_view()
{
	return (this->mp_ds_view);
}
