
#include "depth_stencil_view.h"
#include "exceptions/gfx_exception.h"


pulsar::depth_stencil_view::depth_stencil_view(UINT width, UINT height)
{
	this->create_dsv(width, height);
}

pulsar::depth_stencil_view::~depth_stencil_view()
{
	this->destroy_dsv();
}

void	pulsar::depth_stencil_view::create_dsv(UINT width, UINT height)
{
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
	this->create_texture(&td);

	dsvd.Format = DXGI_FORMAT_D32_FLOAT;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	GFX_ASSERT(pulsar::gfx::instance().device()->CreateDepthStencilView(this->texture(), &dsvd, &this->mp_dsv));
}

void	pulsar::depth_stencil_view::destroy_dsv()
{
	if (this->mp_dsv)
	{
		this->mp_dsv->Release();
		this->mp_dsv = NULL;
	}
}

void	pulsar::depth_stencil_view::resize_resource(UINT width, UINT height)
{
	this->destroy_texture();
	this->destroy_dsv();
	this->create_dsv(width, height);
}

void	pulsar::depth_stencil_view::clear()
{
	pulsar::gfx::instance().device_context()->ClearDepthStencilView(this->mp_dsv, D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

void	pulsar::depth_stencil_view::clear(D3D11_RECT *rect)
{
	float clear_color[4] = { 1.0f, 1.0f, 1.0f, 1.0 };
	pulsar::gfx::instance().device_context()->ClearView(this->mp_dsv, clear_color, rect, 1u);
}

ID3D11DepthStencilView	*pulsar::depth_stencil_view::dsv()
{
	return (this->mp_dsv);
}
