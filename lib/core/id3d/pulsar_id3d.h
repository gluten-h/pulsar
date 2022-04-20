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
	class id3d
	{
	private:
		IDXGIFactory		*mp_idxgi_factory = NULL;
		ID3D11Device		*mp_device = NULL;
		ID3D11DeviceContext	*mp_device_context = NULL;

	public:
		id3d()
		{
			HRESULT hr;

			WIN_ASSERT(CoInitializeEx(NULL, COINIT_MULTITHREADED));
			GFX_ASSERT(CreateDXGIFactory(IID_IDXGIFactory, (void**)&this->mp_idxgi_factory));

			UINT device_flags = 0u;
			device_flags |= D3D11_CREATE_DEVICE_DEBUG;

			GFX_ASSERT(D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, device_flags, NULL, NULL, D3D11_SDK_VERSION, &this->mp_device, NULL, &this->mp_device_context));

			//PULSAR::RESOURCE_MANAGER::add_terminate(PULSAR_D3D::terminate);
		}
		~id3d()
		{
			this->mp_device->Release();
			this->mp_device_context->Release();
			this->mp_idxgi_factory->Release();
			CoUninitialize();
		}

		IDXGIFactory	*idxgi_factory() const
		{
			return (this->mp_idxgi_factory);
		}
		ID3D11Device	*device() const
		{
			return (this->mp_device);
		}
		ID3D11DeviceContext		*device_context() const
		{
			return (this->mp_device_context);
		}
	};
}
