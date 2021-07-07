#pragma once

#include "grng_bindable.h"


class grng_render_texture : public GRNG_BINDABLE
{
private:
	ID3D11RenderTargetView		*texture_rtv = NULL;
	ID3D11ShaderResourceView	*texture_srv = NULL;
	UINT						slot = 0u;


	void		set_rt_memory(ID3D11Texture2D *texture)
	{
		HRESULT hr;

		D3D11_TEXTURE2D_DESC td;
		D3D11_RENDER_TARGET_VIEW_DESC rtvd;
		D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
		ZeroMemory(&rtvd, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
		ZeroMemory(&srvd, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

		texture->GetDesc(&td);

		rtvd.Format = td.Format;
		rtvd.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		rtvd.Texture2D.MipSlice = 0u;
		hr = this->device->CreateRenderTargetView(texture, &rtvd, &this->texture_rtv);

		srvd.Format = td.Format;
		srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvd.Texture2D.MipLevels = 1u;
		srvd.Texture2D.MostDetailedMip = 0u;
		hr = this->device->CreateShaderResourceView(texture, &srvd, &this->texture_srv);
	}

	void		remove_rt_memory()
	{
		if (this->texture_rtv)
		{
			this->texture_rtv->Release();
			this->texture_rtv = NULL;
		}
		if (this->texture_srv)
		{
			this->texture_srv->Release();
			this->texture_srv = NULL;
		}
	}

public:
	grng_render_texture		&operator=(const grng_render_texture &rt)
	{
		this->texture_rtv = rt.texture_rtv;
		this->texture_srv = rt.texture_srv;
		this->slot = slot;

		return (*this);
	}

	grng_render_texture() : GRNG_BINDABLE()
	{
		this->type = GRNG_BINDABLE_TYPE::RENDER_TEXTURE;
	}
	grng_render_texture(ID3D11Texture2D *texture, UINT slot = 0u) : GRNG_BINDABLE()
	{
		this->type = GRNG_BINDABLE_TYPE::RENDER_TEXTURE;

		this->set_rt_memory(texture);
		this->set_slot(slot);
	}

	~grng_render_texture()
	{
		this->remove_rt_memory();
	}

	void		set(ID3D11Texture2D *texture)
	{
		this->remove_rt_memory();
		this->set_rt_memory(texture);
	}

	void		set_slot(UINT slot)
	{
		this->slot = slot;
	}


	ID3D11RenderTargetView		*get_render_target()
	{
		return (this->texture_rtv);
	}

	ID3D11ShaderResourceView	*get_shader_resource()
	{
		return (this->texture_srv);
	}


	static GRNG_BINDABLE		*create_manager_ptr()
	{
		grng_render_texture *rt = new grng_render_texture;

		return (rt);
	}


	void		bind_as_rtv(ID3D11DepthStencilView *depth_stencil_view)
	{
		this->device_context->OMSetRenderTargets(1u, &this->texture_rtv, depth_stencil_view);
	}

	void		bind() override
	{
		this->device_context->PSSetShaderResources(this->slot, 1u, &this->texture_srv);
	}


	void		destroy() override
	{
		this->remove_rt_memory();
	}
};

using GRNG_RENDER_TEXTURE = grng_render_texture;
