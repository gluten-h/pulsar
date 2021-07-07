
#include "grng_window.h"


void		grng_window::create(const LPCWSTR win_name, const DWORD win_style, int x, int y, int w, int h, GRNG_WIN_PROC_DEF win_proc, void *win_proc_data, HINSTANCE h_instance)
{
	HRESULT hr;

	RECT wr = { 0, 0, w, h };
	AdjustWindowRect(&wr, win_style, FALSE);

	HWND hwnd = CreateWindowEx(NULL, GRNG_WIN_CLASS_NAME, win_name, win_style, x, y, wr.right - wr.left, wr.bottom - wr.top, NULL, NULL, h_instance, NULL);
	this->hwnd = hwnd;
	this->win_proc = win_proc;
	this->win_proc_data = win_proc_data;

	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
	scd.BufferCount = 1u;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.SampleDesc.Count = 1u;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = hwnd;
	scd.Windowed = TRUE;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	hr = this->idxgi_factory->CreateSwapChain(this->device, &scd, &this->swap_chain);
	hr = this->swap_chain->GetBuffer(0u, __uuidof(ID3D11Texture2D), (LPVOID*)&this->back_buffer_texture);
	hr = this->device->CreateRenderTargetView(this->back_buffer_texture, NULL, &this->back_buffer);

	this->deferred_buffer.set_deferred_buffer((float)w, (float)h);
}

void		grng_window::destroy()
{
	this->win_id = -1;
	this->hwnd = NULL;
	this->win_proc = NULL;
	this->win_proc_data = NULL;

	this->win_update.clear();

	if (this->swap_chain)
	{
		this->swap_chain->Release();
		this->swap_chain = NULL;
	}
	if (this->back_buffer_texture)
	{
		this->back_buffer_texture->Release();
		this->back_buffer_texture = NULL;
	}
	if (this->back_buffer)
	{
		this->back_buffer->Release();
		this->back_buffer = NULL;
	}

	this->deferred_buffer.destroy();

	this->curr_camera = NULL;
	this->curr_scene = NULL;
}
