#pragma once

#include "igrng_d3d.h"


class grng_texture2d : public GRNG_ID3D
{
private:
	ID3D11Texture2D		*texture = NULL;


	void				set_texture_memory(float width, float height, DXGI_FORMAT format, UINT bind_flags, UINT cpu_access_flags)
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
		hr = this->device->CreateTexture2D(&td, NULL, &this->texture);
	}

	void				remove_texture_memory()
	{
		if (this->texture)
		{
			this->texture->Release();
			this->texture = NULL;
		}
	}

public:
	grng_texture2d		&operator=(const grng_texture2d &t)
	{
		this->texture = t.texture;

		return (*this);
	}

	grng_texture2d() : GRNG_ID3D(){ }
	grng_texture2d(float width, float height, DXGI_FORMAT format, UINT bind_flags = 0u, UINT cpu_access_flags = 0u) : GRNG_ID3D()
	{
		this->set_texture_memory(width, height, format, bind_flags, cpu_access_flags);
	}

	~grng_texture2d()
	{
		this->remove_texture_memory();
	}

	void				set_texture(float width, float height, DXGI_FORMAT format, UINT bind_flags = 0u, UINT cpu_access_flags = 0u)
	{
		this->remove_texture_memory();
		this->set_texture_memory(width, height, format, bind_flags, cpu_access_flags);
	}

	ID3D11Texture2D		*get_texture() const
	{
		return (this->texture);
	}


	void				destroy()
	{
		this->remove_texture_memory();
	}
};

using GRNG_TEXTURE2D = grng_texture2d;
