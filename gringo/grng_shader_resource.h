#pragma once

#include "grng_bindable.h"


class grng_shader_resource : public GRNG_BINDABLE
{
private:
	ID3D11ShaderResourceView		*texture_srv = NULL;

	
	void		set_sr_memory(ID3D11Texture2D *texture)
	{
		HRESULT hr;

		D3D11_TEXTURE2D_DESC td;
		D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
		texture->GetDesc(&td);

		srvd.Format = td.Format;
		srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvd.Texture2D.MipLevels = 0u;
		srvd.Texture2D.MostDetailedMip = 1u;
		hr = this->device->CreateShaderResourceView(texture, &srvd, &this->texture_srv);
	}

	void		remove_sr_memory()
	{
		if (this->texture_srv)
		{
			this->texture_srv->Release();
			this->texture_srv = NULL;
		}
	}

public:
	grng_shader_resource(ID3D11Texture2D *texture) : GRNG_BINDABLE()
	{
		this->set_sr_memory(texture);
	}

	~grng_shader_resource()
	{
		this->remove_sr_memory();
	}

	void		set_texture(ID3D11Texture2D *texture)
	{
		this->remove_sr_memory();
		this->set_sr_memory(texture);
	}

	ID3D11ShaderResourceView		*get_shader_resource() const
	{
		return (this->texture_srv);
	}


	void		bind() override
	{
		this->device_context->PSSetShaderResources(0u, 1u, &this->texture_srv);
	}
};

using GRNG_SHADER_RESOURCE = grng_shader_resource;
