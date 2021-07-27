
#include "grng_depth_stencil_view.h"


void				grng_depth_stencil_view::set_ds_memory(float width, float height)
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
	GRNG_GFX_ASSERT(this->device->CreateTexture2D(&td, NULL, &this->ds_texture));

	dsvd.Format = DXGI_FORMAT_D32_FLOAT;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	GRNG_GFX_ASSERT(this->device->CreateDepthStencilView(this->ds_texture, &dsvd, &this->ds_view));
}

void						grng_depth_stencil_view::remove_ds_texture_memory()
{
	if (this->ds_texture)
	{
		ULONG ref_count = this->ds_texture->Release();
		if (ref_count == 0)
			this->ds_texture = NULL;
	}
}

void						grng_depth_stencil_view::remove_ds_view_memory()
{
	if (this->ds_view)
	{
		ULONG ref_count = this->ds_view->Release();
		if (ref_count == 0)
			this->ds_view = NULL;
	}
}

void				grng_depth_stencil_view::remove_ds_memory()
{
	this->remove_ds_texture_memory();
	this->remove_ds_view_memory();
}

void				grng_depth_stencil_view::set(float width, float height)
{
	this->remove_ds_memory();
	this->set_ds_memory(width, height);
}

GRNG_BINDABLE		*grng_depth_stencil_view::create_manager_ptr()
{
	grng_depth_stencil_view *dsv = new grng_depth_stencil_view;

	return (dsv);
}
