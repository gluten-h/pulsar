
#include "depth_stencil_view.h"


void	PULSAR::depth_stencil_view::create_ds_view(float width, float height)
{
	HRESULT hr;

	D3D11_TEXTURE2D_DESC td;
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));

	td.Width = width;
	td.Height = height;
	td.MipLevels = 1u;
	td.ArraySize = 1u;
	td.Format = DXGI_FORMAT_D32_FLOAT;
	td.SampleDesc.Count = 1u;
	td.SampleDesc.Quality = 0u;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	td.CPUAccessFlags = 0u;
	td.MiscFlags = 0u;
	GFX_ASSERT(PULSAR::gfx::get().device()->CreateTexture2D(&td, NULL, &this->mp_texture));

	dsvd.Format = DXGI_FORMAT_D32_FLOAT;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	GFX_ASSERT(PULSAR::gfx::get().device()->CreateDepthStencilView(this->mp_texture, &dsvd, &this->mp_ds_view));
}

void	PULSAR::depth_stencil_view::free()
{
	if (this->mp_texture)
	{
		this->mp_texture->Release();
		this->mp_texture = NULL;
	}
	if (this->mp_ds_view)
	{
		this->mp_ds_view->Release();
		this->mp_ds_view = NULL;
	}
}

void	PULSAR::depth_stencil_view::set(float width, float height)
{
	this->free();
	this->create_ds_view(width, height);
}

ID3D11Texture2D		*PULSAR::depth_stencil_view::get_texture()
{
	return (this->mp_texture);
}
ID3D11DepthStencilView		*PULSAR::depth_stencil_view::get_view()
{
	return (this->mp_ds_view);
}
