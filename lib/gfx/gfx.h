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
#include <wrl.h>
#include <tchar.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <dxgi1_2.h>
#include <dxgi.h>
#include <d3dcompiler.h>

#include <DirectXTex.h>
#include <DDSTextureLoader.h>
#include <WICTextureLoader.h>

using namespace DirectX;
using namespace Microsoft::WRL;

#include "utils/singleton.h"


namespace pulsar
{
	class gfx : public pulsar::singleton<gfx>
	{
	private:
		IDXGIFactory *mp_idxgi_factory = NULL;
		ID3D11Device *mp_device = NULL;
		ID3D11DeviceContext *mp_device_context = NULL;

	public:
		gfx();
		~gfx();

		IDXGIFactory	*idxgi_factory();
		ID3D11Device	*device();
		ID3D11DeviceContext		*device_context();

		void	draw_indexed(UINT index_count) const;
	};
}
