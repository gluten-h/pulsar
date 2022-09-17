
#include "render_texture.h"
#include "exceptions/gfx_exception.h"


pulsar::render_texture::render_texture(UINT width, UINT height, DXGI_FORMAT format, UINT slot)
{
	this->create_rt(width, height, format);
	this->m_slot = slot;
}

pulsar::render_texture::~render_texture()
{
	this->destroy_rt();
}

void	pulsar::render_texture::create_rt(UINT width, UINT height, DXGI_FORMAT format)
{
	D3D11_TEXTURE2D_DESC td;
	D3D11_RENDER_TARGET_VIEW_DESC rtvd;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
	ZeroMemory(&rtvd, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
	ZeroMemory(&srvd, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

	td.Width = width;
	td.Height = height;
	td.MipLevels = 1u;
	td.ArraySize = 1u;
	td.Format = format;
	td.SampleDesc.Count = 1u;
	td.SampleDesc.Quality = 0u;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	td.CPUAccessFlags = 0u;
	td.MiscFlags = 0u;
	this->create_texture(&td);

	rtvd.Format = format;
	rtvd.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	GFX_ASSERT(pulsar::gfx::instance().device()->CreateRenderTargetView(this->mp_texture, &rtvd, &this->mp_rtv));

	srvd.Format = format;
	srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvd.Texture2D.MipLevels = 1u;
	GFX_ASSERT(pulsar::gfx::instance().device()->CreateShaderResourceView(this->mp_texture, &srvd, &this->mp_srv));
}

void	pulsar::render_texture::destroy_rt()
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
}

ID3D11RenderTargetView	*pulsar::render_texture::rtv()
{
	return (this->mp_rtv);
}

ID3D11ShaderResourceView	*pulsar::render_texture::srv()
{
	return (this->mp_srv);
}

void	pulsar::render_texture::set(UINT width, UINT height, DXGI_FORMAT format)
{
	this->destroy_texture();
	this->destroy_rt();
	this->create_rt(width, height, format);
}

void	pulsar::render_texture::set_slot(UINT slot)
{
	this->m_slot = slot;
}

void	pulsar::render_texture::resize_resource(UINT width, UINT height)
{
	if (this->mp_texture)
	{
		D3D11_TEXTURE2D_DESC td;
		this->mp_texture->GetDesc(&td);
		this->set(width, height, td.Format);
	}
}

void	pulsar::render_texture::clear()
{
	float clear_color[4] = { 0.0f, 0.0f, 0.0f, 1.0 };
	pulsar::gfx::instance().device_context()->ClearRenderTargetView(this->mp_rtv, clear_color);
}

void	pulsar::render_texture::bind_srv() const
{
	pulsar::gfx::instance().device_context()->PSSetShaderResources(this->m_slot, 1u, &this->mp_srv);
}

void	pulsar::render_texture::bind_rtv(ID3D11DepthStencilView *dsv) const
{
	pulsar::gfx::instance().device_context()->OMSetRenderTargets(1u, &this->mp_rtv, dsv);
}

void	pulsar::render_texture::unbind_srv() const
{
	ID3D11ShaderResourceView *null[1] = { NULL };
	pulsar::gfx::instance().device_context()->PSSetShaderResources(this->m_slot, 1u, null);
}

void	pulsar::render_texture::unbind_rtv() const
{
	ID3D11RenderTargetView *null[1] = { NULL };
	pulsar::gfx::instance().device_context()->OMSetRenderTargets(1u, null, NULL);
}
