
#include "depth_stencil_view.h"


void	PULSAR::DEPTH_STENCIL_VIEW::set_ds_memory(float width, float height)
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
	GFX_ASSERT(this->device->CreateTexture2D(&td, NULL, &this->ds_texture));

	dsvd.Format = DXGI_FORMAT_D32_FLOAT;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	GFX_ASSERT(this->device->CreateDepthStencilView(this->ds_texture, &dsvd, &this->ds_view));
}

void	PULSAR::DEPTH_STENCIL_VIEW::remove_ds_texture_memory()
{
	if (this->ds_texture)
	{
		ULONG ref_count = this->ds_texture->Release();
		if (ref_count == 0)
			this->ds_texture = NULL;
	}
}

void	PULSAR::DEPTH_STENCIL_VIEW::remove_ds_view_memory()
{
	if (this->ds_view)
	{
		ULONG ref_count = this->ds_view->Release();
		if (ref_count == 0)
			this->ds_view = NULL;
	}
}

void	PULSAR::DEPTH_STENCIL_VIEW::remove_ds_memory()
{
	this->remove_ds_texture_memory();
	this->remove_ds_view_memory();
}

void	PULSAR::DEPTH_STENCIL_VIEW::set(float width, float height)
{
	this->remove_ds_memory();
	this->set_ds_memory(width, height);
}


PULSAR::DEPTH_STENCIL_VIEW		*PULSAR::DEPTH_STENCIL_VIEW::create()
{
	return ((PULSAR::DEPTH_STENCIL_VIEW*)PULSAR::BINDABLE::add_to_manager(new PULSAR::DEPTH_STENCIL_VIEW));
}
