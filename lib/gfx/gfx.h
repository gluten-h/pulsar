#pragma once

#include <Windows.h>
#include <wrl.h>
#include <tchar.h>
#include <d3d11_1.h>
#include <dxgi.h>
#include <d3dcompiler.h>

#include "DirectXTex.h"
#include "DDSTextureLoader.h"
#include "WICTextureLoader.h"

using namespace DirectX;
using namespace Microsoft::WRL;

#include "utils/singleton.h"


namespace pulsar
{
	class gfx : public pulsar::singleton<gfx>
	{
	private:
		IDXGIFactory *mp_idxgi_factory = NULL;
		ID3D11Device1 *mp_device = NULL;
		ID3D11DeviceContext1 *mp_device_context = NULL;

	public:
		gfx();
		~gfx();

		IDXGIFactory	*idxgi_factory();
		ID3D11Device1	*device();
		ID3D11DeviceContext1	*device_context();

		void	draw_indexed(UINT index_count) const;
	};
}
