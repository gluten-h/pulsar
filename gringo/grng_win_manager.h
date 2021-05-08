#pragma once


#include "igrng_d3d.h"
#include "grng_piston.h"
#include "grng_components.h"
#include "grng_gfx.h"

#include <algorithm>
#include <unordered_map>
#include <vector>


#define GRNG_MAX_WIN_COUNT 16
#define GRNG_WIN_CLASS_NAME L"gringo"


struct								grng_win
{
	HWND							hwnd = NULL;
	void							(*win_proc)(UINT, void*) = NULL;
	void							*win_proc_data = NULL;

	DXGI_SWAP_CHAIN_DESC			scd;
	D3D11_DEPTH_STENCIL_DESC		dsd;
	D3D11_TEXTURE2D_DESC			dtd;
	D3D11_DEPTH_STENCIL_VIEW_DESC	dsvd;
	IDXGISwapChain					*swap_chain = NULL;
	ID3D11RenderTargetView			*back_buffer = NULL;
	ID3D11DepthStencilState			*depth_stencil_state = NULL;
	ID3D11DepthStencilView			*depth_stencil_view = NULL;
	D3D11_VIEWPORT					viewport;


	GRNG_CAMERA						*curr_camera = NULL;


	void		bind() const
	{
		ID3D11DeviceContext *device_context = GRNG_D3D::get_device_context();

		device_context->OMSetRenderTargets(1, &this->back_buffer, this->depth_stencil_view);
		device_context->OMSetDepthStencilState(this->depth_stencil_state, 1u);
		device_context->RSSetViewports(1, &this->viewport);
		device_context->ClearRenderTargetView(this->back_buffer, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		device_context->ClearDepthStencilView(this->depth_stencil_view, D3D11_CLEAR_DEPTH, 1.0f, 0u);


		this->curr_camera->update(this->viewport.Width, this->viewport.Height);
		GRNG_GFX::set_camera(this->curr_camera);
	}
};

using GRNG_WIN = grng_win;


class grng_wm : public IGRNG_D3D
{
private:
	static HINSTANCE			h_instance;
	static WNDCLASSEX			wc;
	static MSG					msg;

	static GRNG_PISTON<GRNG_WIN, GRNG_MAX_WIN_COUNT>			win;
	static std::unordered_map<HWND, int>						hwnd_map;
	static const GRNG_IPISTON<GRNG_WIN, GRNG_MAX_WIN_COUNT>		*iwin;


	static LRESULT CALLBACK	win_proc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
	{
		int win_id = grng_wm::hwnd_map[hwnd];
		const GRNG_WIN *win_ptr = grng_wm::win.get(win_id);

		if (msg == WM_DESTROY)
		{
			grng_wm::destroy_win_memory(win_id);
			if (grng_wm::iwin->size <= 0)
			{
				PostQuitMessage(0);
				return (0);
			}
		}

		if (win_ptr->win_proc)
			win_ptr->win_proc(msg, win_ptr->win_proc_data);

		return (DefWindowProc(hwnd, msg, w_param, l_param));
	}


	static void			init_wnd_class(const HINSTANCE h_instance)
	{
		grng_wm::h_instance = h_instance;
		ZeroMemory(&grng_wm::wc, sizeof(WNDCLASSEX));

		grng_wm::wc.cbSize = sizeof(WNDCLASSEX);
		grng_wm::wc.style = CS_OWNDC;
		grng_wm::wc.lpfnWndProc = grng_wm::win_proc;
		grng_wm::wc.cbClsExtra = 0;
		grng_wm::wc.cbWndExtra = 0;
		grng_wm::wc.hInstance = h_instance;
		grng_wm::wc.hIcon = NULL;
		grng_wm::wc.hCursor = NULL;
		grng_wm::wc.hbrBackground = NULL;
		grng_wm::wc.lpszMenuName = NULL;
		grng_wm::wc.lpszClassName = GRNG_WIN_CLASS_NAME;
		grng_wm::wc.hIconSm = NULL;
		grng_wm::wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
		RegisterClassEx(&grng_wm::wc);
	}

	static void			init_win()
	{
		grng_wm::iwin = grng_wm::win.get_ipiston();

		int i = -1;
		while (++i < GRNG_MAX_WIN_COUNT)
		{
			grng_wm::destroy_win_memory(i);
		}
	}


	static void			destroy_win_memory(int win_id)
	{
		GRNG_WIN *win_ptr = grng_wm::win.get(win_id);

		grng_wm::hwnd_map.erase(win_ptr->hwnd);
		win_ptr->hwnd = NULL;
		win_ptr->win_proc = NULL;
		win_ptr->win_proc_data = NULL;

		ZeroMemory(&win_ptr->scd, sizeof(DXGI_SWAP_CHAIN_DESC));
		ZeroMemory(&win_ptr->dsd, sizeof(D3D11_DEPTH_STENCIL_DESC));
		ZeroMemory(&win_ptr->dtd, sizeof(D3D11_TEXTURE2D_DESC));
		ZeroMemory(&win_ptr->dsvd, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
		ZeroMemory(&win_ptr->viewport, sizeof(D3D11_VIEWPORT));


		if (win_ptr->swap_chain)
		{
			win_ptr->swap_chain->Release();
			win_ptr->swap_chain = NULL;
		}
		if (win_ptr->back_buffer)
		{
			win_ptr->back_buffer->Release();
			win_ptr->back_buffer = NULL;
		}
		if (win_ptr->depth_stencil_state)
		{
			win_ptr->depth_stencil_state->Release();
			win_ptr->depth_stencil_state = NULL;
		}
		if (win_ptr->depth_stencil_view)
		{
			win_ptr->depth_stencil_view->Release();
			win_ptr->depth_stencil_view = NULL;
		}

		grng_wm::win.remove_secure(win_id);
	}

public:
	static void			create(const HINSTANCE h_instance)
	{
		IGRNG_D3D();
		grng_wm::init_wnd_class(h_instance);
		grng_wm::init_win();
	}

	static void			destroy()
	{
		int i = -1;
		while (++i < GRNG_MAX_WIN_COUNT)
		{
			grng_wm::win.remove_secure(i);
		}
	}


	static int			create_win(const LPCWSTR win_name, const DWORD win_style, int x, int y, int w, int h, const HWND hwnd_parent, void (*win_proc)(UINT, void *), void* win_proc_data)
	{
		if (grng_wm::iwin->size >= GRNG_MAX_WIN_COUNT)
			return (-1);

		RECT wr = { 0, 0, w, h };
		AdjustWindowRect(&wr, win_style, FALSE);
		if (HWND hwnd = CreateWindowEx(NULL, GRNG_WIN_CLASS_NAME, win_name, win_style, x, y, wr.right - wr.left, wr.bottom - wr.top, hwnd_parent, NULL, grng_wm::h_instance, NULL))
		{
			GRNG_WIN *win_ptr = grng_wm::win.get(grng_wm::win.next_id());

			win_ptr->hwnd = hwnd;
			win_ptr->win_proc = win_proc;
			win_ptr->win_proc_data = win_proc_data;

			win_ptr->scd.BufferCount = 1;
			win_ptr->scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			win_ptr->scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			win_ptr->scd.OutputWindow = hwnd;
			win_ptr->scd.SampleDesc.Count = 1;
			win_ptr->scd.SampleDesc.Quality = 0;
			win_ptr->scd.Windowed = TRUE;
			win_ptr->scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

			HRESULT hr;
			ID3D11Texture2D *p_back_buffer;
			hr = grng_wm::idxgi_factory->CreateSwapChain(grng_wm::device, &win_ptr->scd, &win_ptr->swap_chain);
			hr = win_ptr->swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&p_back_buffer);
			hr = grng_wm::device->CreateRenderTargetView(p_back_buffer, NULL, &win_ptr->back_buffer);
			p_back_buffer->Release();

			win_ptr->dsd.DepthEnable = TRUE;
			win_ptr->dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			win_ptr->dsd.DepthFunc = D3D11_COMPARISON_LESS;
			hr = grng_wm::device->CreateDepthStencilState(&win_ptr->dsd, &win_ptr->depth_stencil_state);

			ID3D11Texture2D *ds_txt;
			win_ptr->dtd.Width = w;
			win_ptr->dtd.Height = h;
			win_ptr->dtd.MipLevels = 1u;
			win_ptr->dtd.ArraySize = 1u;
			win_ptr->dtd.Format = DXGI_FORMAT_D32_FLOAT;
			win_ptr->dtd.SampleDesc.Count = 1u;
			win_ptr->dtd.SampleDesc.Quality = 0u;
			win_ptr->dtd.Usage = D3D11_USAGE_DEFAULT;
			win_ptr->dtd.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			win_ptr->dtd.CPUAccessFlags = 0u;
			win_ptr->dtd.MiscFlags = 0u;
			hr = grng_wm::device->CreateTexture2D(&win_ptr->dtd, NULL, &ds_txt);

			win_ptr->dsvd.Format = DXGI_FORMAT_D32_FLOAT;
			win_ptr->dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			win_ptr->dsvd.Texture2D.MipSlice = 0u;
			hr = grng_wm::device->CreateDepthStencilView(ds_txt, &win_ptr->dsvd, &win_ptr->depth_stencil_view);
			ds_txt->Release();

			win_ptr->viewport.TopLeftX = 0.0f;
			win_ptr->viewport.TopLeftY = 0.0f;
			win_ptr->viewport.Width = (FLOAT)w;
			win_ptr->viewport.Height = (FLOAT)h;
			win_ptr->viewport.MinDepth = 0.0f;
			win_ptr->viewport.MaxDepth = 1.0f;

			int win_id = grng_wm::win.add(*win_ptr);
			grng_wm::hwnd_map[hwnd] = win_id;

			return (win_id);
		}
		return (-1);
	}

	static void			destroy_win_secure(unsigned int win_id)
	{
		GRNG_WIN *win_ptr = grng_wm::win.get_secure(win_id);
		if (!win_ptr)
			return;

		grng_wm::destroy_win_memory(win_id);
	}

	static void			destroy_win(unsigned int win_id)
	{
		grng_wm::destroy_win_memory(win_id);
	}


	static bool			win_event()
	{
		if (PeekMessage(&grng_wm::msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&grng_wm::msg);
			DispatchMessage(&grng_wm::msg);
		}

		return (grng_wm::msg.message != WM_QUIT);
	}


	static const GRNG_IPISTON<GRNG_WIN, GRNG_MAX_WIN_COUNT>		*get_iwin()
	{
		return (grng_wm::iwin);
	}


	static void			set_camera_secure(unsigned int win_id, GRNG_CAMERA &cam)
	{
		GRNG_WIN *win_ptr = grng_wm::win.get_secure(win_id);
		if (!win_ptr)
			return;
		win_ptr->curr_camera = &cam;
	}

	static void			set_camera(unsigned int win_id, GRNG_CAMERA &cam)
	{
		GRNG_WIN *win_ptr = grng_wm::win.get(win_id);
		win_ptr->curr_camera = &cam;
	}
};


using GRNG_WM = grng_wm;

