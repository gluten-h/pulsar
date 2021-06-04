#pragma once

#include "grng_asset.h"


class grng_texture : public GRNG_ASSET
{
private:
	ID3D11ShaderResourceView		*texture_srv = NULL;
	UINT							slot = 0u;


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
	grng_texture	&operator=(const grng_texture &t)
	{
		this->texture_srv = t.texture_srv;
		this->slot = t.slot;

		return (*this);
	}

	grng_texture() : GRNG_ASSET(){ }
	grng_texture(const LPCWSTR file, UINT slot = 0u) : GRNG_ASSET()
	{
		this->set_texture_memory(file);
		this->set_slot(slot);
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

	void		set_slot(UINT slot)
	{
		this->slot = slot;
	}


	void		bind() override
	{
		this->device_context->PSSetShaderResources(this->slot, 1u, &this->texture_srv);
	}

	void		destroy() override
	{
		this->remove_texture_memory();
	}
};

using GRNG_TEXTURE = grng_texture;
