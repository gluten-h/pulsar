#pragma once

#include "grng_asset.h"


class grng_texture : public GRNG_ASSET
{
private:
	ID3D11ShaderResourceView		*texture_srv = NULL;


	void		set_texture_memory(const LPCWSTR file)
	{
		HRESULT hr = D3DX11CreateShaderResourceViewFromFile(this->device, file, NULL, NULL, &this->texture_srv, NULL);
	}

	void		remove_texture_memory()
	{
		if (this->texture_srv)
		{
			this->texture_srv->Release();
			this->texture_srv = NULL;
		}
	}

public:
	grng_texture(const LPCWSTR file) : GRNG_ASSET()
	{
		this->set_texture_memory(file);
	}

	~grng_texture()
	{
		this->remove_texture_memory();
	}

	void		set_texture(const LPCWSTR file)
	{
		this->remove_texture_memory();
		this->set_texture_memory(file);
	}


	void		bind() override
	{
		this->device_context->PSSetShaderResources(0u, 1u, &this->texture_srv);
	}
};

using GRNG_TEXTURE = grng_texture;
