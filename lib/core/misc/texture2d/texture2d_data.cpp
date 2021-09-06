
#include "texture2d.h"


void		PULSAR::TEXTURE2D::set_texture_memory(float width, float height, DXGI_FORMAT format, UINT bind_flags, UINT cpu_access_flags)
{
	HRESULT hr;

	D3D11_TEXTURE2D_DESC td;
	td.Width = width;
	td.Height = height;
	td.MipLevels = 1;
	td.ArraySize = 1;
	td.Format = format;
	td.SampleDesc.Count = 1;
	td.SampleDesc.Quality = 0;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = bind_flags;
	td.CPUAccessFlags = cpu_access_flags;
	td.MiscFlags = 0u;
	GFX_ASSERT(this->device->CreateTexture2D(&td, NULL, &this->texture));
}

void		PULSAR::TEXTURE2D::remove_texture_memory()
{
	if (this->texture)
	{
		ULONG ref_count = this->texture->Release();
		if (ref_count == 0)
			this->texture = NULL;
	}
}

void		PULSAR::TEXTURE2D::set_texture(float width, float height, DXGI_FORMAT format, UINT bind_flags, UINT cpu_access_flags)
{
	this->remove_texture_memory();
	this->set_texture_memory(width, height, format, bind_flags, cpu_access_flags);
}
