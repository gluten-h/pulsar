#pragma once

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "dxgi")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "D3DCompiler.lib")

#pragma comment(lib, "dxerr.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "uuid.lib")


#include <Windows.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <dxgi1_2.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include <D3DX10math.h>
#include <DirectXMath.h>

#include <DirectXTex.h>
#include <DDSTextureLoader.h>
#include <WICTextureLoader.h>

using namespace DirectX;

#include <cstddef>
#include <tchar.h>

#include "grng_exc_macros.h"
#include "grng_utils.h"
#include "grng_resource_manager.h"


class grng_d3d
{
protected:
	static bool						is_initialized;

	static IDXGIFactory				*idxgi_factory;
	static ID3D11Device				*device;
	static ID3D11DeviceContext		*device_context;

public:
	static void				create()
	{
		if (grng_d3d::is_initialized)
			return;

		HRESULT hr;

		GRNG_WIN_ASSERT(CoInitializeEx(NULL, COINIT_MULTITHREADED));
		GRNG_GFX_ASSERT(CreateDXGIFactory(IID_IDXGIFactory, (void**)&grng_d3d::idxgi_factory));
		GRNG_GFX_ASSERT(D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL, D3D11_SDK_VERSION, &grng_d3d::device, NULL, &grng_d3d::device_context));

		GRNG_RESOURCE_MANAGER::add_terminate(grng_d3d::destroy);
		grng_d3d::is_initialized = true;
	}

	static void				destroy()
	{
		grng_d3d::idxgi_factory->Release();
		grng_d3d::device->Release();
		grng_d3d::device_context->Release();
		CoUninitialize();
	}


	static IDXGIFactory					*get_idxgi_factory()
	{
		return (grng_d3d::idxgi_factory);
	}

	static ID3D11Device					*get_device()
	{
		return (grng_d3d::device);
	}

	static ID3D11DeviceContext			*get_device_context()
	{
		return (grng_d3d::device_context);
	}
};


using GRNG_D3D = grng_d3d;

