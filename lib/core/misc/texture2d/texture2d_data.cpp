//
//#include "texture2d.h"
//
//
//void	PULSAR::texture2d::create_texture2d(UINT width, UINT height, DXGI_FORMAT format, UINT bind_flags, UINT cpu_access_flags)
//{
//	D3D11_TEXTURE2D_DESC td;
//	td.Width = width;
//	td.Height = height;
//	td.MipLevels = 1;
//	td.ArraySize = 1;
//	td.Format = format;
//	td.SampleDesc.Count = 1;
//	td.SampleDesc.Quality = 0;
//	td.Usage = D3D11_USAGE_DEFAULT;
//	td.BindFlags = bind_flags;
//	td.CPUAccessFlags = cpu_access_flags;
//	td.MiscFlags = 0u;
//	GFX_ASSERT(PULSAR::gfx::get().device()->CreateTexture2D(&td, NULL, &this->mp_texture));
//}
//
//void	PULSAR::texture2d::free()
//{
//	if (this->mp_texture)
//	{
//		ULONG ref_count = this->mp_texture->Release();
//		if (ref_count == 0)
//			this->mp_texture = NULL;
//	}
//}
//
//void	PULSAR::texture2d::set(UINT width, UINT height, DXGI_FORMAT format, UINT bind_flags, UINT cpu_access_flags)
//{
//	this->free();
//	this->create_texture2d(width, height, format, bind_flags, cpu_access_flags);
//}
//
//ID3D11Texture2D		*PULSAR::texture2d::get()
//{
//	return (this->mp_texture);
//}
