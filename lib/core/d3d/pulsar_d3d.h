#pragma once

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "dxgi")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "D3DCompiler.lib")

#pragma comment(lib, "dxerr.lib")
#pragma comment(lib, "uuid.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")


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

#include "pulsar_exc.h"
#include "pulsar_utils.h"
#include "pulsar_resource_manager.h"


namespace PULSAR
{
	class PULSAR_D3D
	{
	protected:
		static bool		is_initialized;

		static IDXGIFactory			*idxgi_factory;
		static ID3D11Device			*device;
		static ID3D11DeviceContext	*device_context;

	public:
		static void		init()
		{
			if (PULSAR_D3D::is_initialized)
				return;
			PULSAR_D3D::is_initialized = true;

			HRESULT hr;

			WIN_ASSERT(CoInitializeEx(NULL, COINIT_MULTITHREADED));
			GFX_ASSERT(CreateDXGIFactory(IID_IDXGIFactory, (void**)&PULSAR_D3D::idxgi_factory));
			GFX_ASSERT(D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL, D3D11_SDK_VERSION, &PULSAR_D3D::device, NULL, &PULSAR_D3D::device_context));

			PULSAR::RESOURCE_MANAGER::add_terminate(PULSAR_D3D::terminate);
		}

		static void		terminate()
		{
			PULSAR_D3D::device->Release();
			PULSAR_D3D::device_context->Release();
			PULSAR_D3D::idxgi_factory->Release();
			CoUninitialize();
		}

		static IDXGIFactory		*get_idxgi_factory()
		{
			return (PULSAR_D3D::idxgi_factory);
		}

		static ID3D11Device		*get_device()
		{
			return (PULSAR_D3D::device);
		}

		static ID3D11DeviceContext		*get_device_context()
		{
			return (PULSAR_D3D::device_context);
		}
	};
}
