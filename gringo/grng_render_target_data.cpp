
#include "grng_render_target.h"


void		grng_render_target::set_rt_memory(HWND hwnd, BOOL windowed)
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

	GRNG_GFX_ASSERT(this->idxgi_factory->CreateSwapChain(this->device, &scd, &this->swap_chain));
	GRNG_GFX_ASSERT(this->swap_chain->GetBuffer(0u, __uuidof(ID3D11Texture2D), (LPVOID*)&this->back_buffer_texture));
	GRNG_GFX_ASSERT(this->device->CreateRenderTargetView(this->back_buffer_texture, NULL, &this->back_buffer));
}

void		grng_render_target::remove_swap_chain()
{
	if (this->swap_chain)
	{
		ULONG ref_count = this->swap_chain->Release();
		if (ref_count == 0)
			this->swap_chain = NULL;
	}
}
void		grng_render_target::remove_back_buffer_texture()
{
	if (this->back_buffer_texture)
	{
		ULONG ref_count = this->back_buffer_texture->Release();
		if (ref_count == 0)
			this->back_buffer_texture = NULL;
	}
}
void		grng_render_target::remove_back_buffer()
{
	if (this->back_buffer)
	{
		ULONG ref_count = this->back_buffer->Release();
		if (ref_count == 0)
			this->back_buffer = NULL;
	}
}
void		grng_render_target::remove_rt_memory()
{
	this->remove_swap_chain();
	this->remove_back_buffer_texture();
	this->remove_back_buffer();
}

void		grng_render_target::set(HWND hwnd, BOOL windowed)
{
	this->remove_rt_memory();
	this->set_rt_memory(hwnd, windowed);
}

GRNG_BINDABLE		*grng_render_target::create_manager_ptr()
{
	GRNG_RENDER_TARGET *rt = new GRNG_RENDER_TARGET;

	return (rt);
}
