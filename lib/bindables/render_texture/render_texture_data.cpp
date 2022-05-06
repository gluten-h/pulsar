
#include "render_texture.h"
#include "exceptions/gfx_exception.h"


void	PULSAR::render_texture::create_rt(float width, float height, DXGI_FORMAT format, UINT bind_flags, UINT cpu_access_flags)
{
	D3D11_TEXTURE2D_DESC td;
	D3D11_RENDER_TARGET_VIEW_DESC rtvd;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
	ZeroMemory(&rtvd, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
	ZeroMemory(&srvd, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

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
	GFX_ASSERT(PULSAR::gfx::get().device()->CreateTexture2D(&td, NULL, &this->mp_texture));

	rtvd.Format = td.Format;
	rtvd.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvd.Texture2D.MipSlice = 0u;
	GFX_ASSERT(PULSAR::gfx::get().device()->CreateRenderTargetView(this->mp_texture, &rtvd, &this->mp_rtv));

	srvd.Format = td.Format;
	srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvd.Texture2D.MipLevels = 1u;
	srvd.Texture2D.MostDetailedMip = 0u;
	GFX_ASSERT(PULSAR::gfx::get().device()->CreateShaderResourceView(this->mp_texture, &srvd, &this->mp_srv));
}

void	PULSAR::render_texture::free()
{
	if (this->mp_rtv)
	{
		this->mp_rtv->Release();
		this->mp_rtv = NULL;
	}
	if (this->mp_srv)
	{
		this->mp_srv->Release();
		this->mp_srv = NULL;
	}
	if (this->mp_texture)
	{
		this->mp_texture->Release();
		this->mp_texture = NULL;
	}
}

void	PULSAR::render_texture::set(float width, float height, DXGI_FORMAT format, UINT bind_flags, UINT cpu_access_flags)
{
	this->free();
	this->create_rt(width, height, format, bind_flags, cpu_access_flags);
}

void	PULSAR::render_texture::set_slot(UINT slot)
{
	this->m_slot = slot;
}

ID3D11DepthStencilView	*&PULSAR::render_texture::ds_view()
{
	return (this->mp_ds_view);
}
