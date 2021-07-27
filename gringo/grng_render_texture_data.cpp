
#include "grng_render_texture.h"


void				grng_render_texture::set_rt_memory(ID3D11Texture2D *texture)
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
	GRNG_GFX_ASSERT(this->device->CreateRenderTargetView(texture, &rtvd, &this->texture_rtv));

	srvd.Format = td.Format;
	srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvd.Texture2D.MipLevels = 1u;
	srvd.Texture2D.MostDetailedMip = 0u;
	GRNG_GFX_ASSERT(this->device->CreateShaderResourceView(texture, &srvd, &this->texture_srv));
}

void						grng_render_texture::remove_rtv()
{
	if (this->texture_rtv)
	{
		ULONG ref_count = this->texture_rtv->Release();
		if (ref_count == 0)
			this->texture_rtv = NULL;
	}
}

void						grng_render_texture::remove_srv()
{
	if (this->texture_srv)
	{
		ULONG ref_count = this->texture_srv->Release();
		if (ref_count == 0)
			this->texture_srv = NULL;
	}
}

void				grng_render_texture::remove_rt_memory()
{
	this->remove_rtv();
	this->remove_srv();
}

void				grng_render_texture::set(ID3D11Texture2D *texture)
{
	this->remove_rt_memory();
	this->set_rt_memory(texture);
}

void				grng_render_texture::set_slot(UINT slot)
{
	this->slot = slot;
}

GRNG_BINDABLE		*grng_render_texture::create_manager_ptr()
{
	grng_render_texture *rt = new grng_render_texture;

	return (rt);
}
