
#include "point_shadow_map.h"
#include "exceptions/gfx_exception.h"
#include "config/config.h"
#include "transform/transform.h"
#include <cassert>


pulsar::point_shadow_map::point_shadow_map() : pulsar::shadow_map()
{
	this->m_view_specs[0].dir = XMFLOAT3(1.0f, 0.0, 0.0);
	this->m_view_specs[0].up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	this->m_view_specs[1].dir = XMFLOAT3(-1.0f, 0.0, 0.0);
	this->m_view_specs[1].up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	this->m_view_specs[2].dir = XMFLOAT3(0.0f, 1.0, 0.0);
	this->m_view_specs[2].up = XMFLOAT3(0.0f, 0.0f, -1.0f);
	this->m_view_specs[3].dir = XMFLOAT3(0.0f, -1.0, 0.0);
	this->m_view_specs[3].up = XMFLOAT3(0.0f, 0.0f, 1.0f);
	this->m_view_specs[4].dir = XMFLOAT3(0.0f, 0.0, 1.0);
	this->m_view_specs[4].up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	this->m_view_specs[5].dir = XMFLOAT3(0.0f, 0.0, -1.0);
	this->m_view_specs[5].up = XMFLOAT3(0.0f, 1.0f, 0.0f);

	this->m_view_cbuffer.set(&this->m_view, pulsar::CBUFFER_TYPE::DYNAMIC);
	this->m_proj_cbuffer.set(&this->m_proj, pulsar::CBUFFER_TYPE::DYNAMIC);
	this->m_view_cbuffer.set_slot(pulsar::VERT_SHADOW_TRANSFORM_VIEW_SLOT);
	this->m_proj_cbuffer.set_slot(pulsar::VERT_SHADOW_TRANSFORM_PROJ_SLOT);
}

pulsar::point_shadow_map::~point_shadow_map()
{
	this->destroy_shadow_map();
}

void	pulsar::point_shadow_map::create_shadow_map(UINT width, UINT height)
{
	assert(("Width isn't equal to height", width == height));

	D3D11_TEXTURE2D_DESC dsv_td;
	D3D11_TEXTURE2D_DESC td;
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
	D3D11_RENDER_TARGET_VIEW_DESC rtvd;

	ZeroMemory(&dsv_td, sizeof(D3D11_TEXTURE2D_DESC));
	ZeroMemory(&td, sizeof(D3D11_TEXTURE2D_DESC));
	ZeroMemory(&dsvd, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	ZeroMemory(&srvd, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	ZeroMemory(&rtvd, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));

	dsv_td.Width = width;
	dsv_td.Height = height;
	dsv_td.MipLevels = 1u;
	dsv_td.ArraySize = 1u;
	dsv_td.Format = DXGI_FORMAT_D32_FLOAT;
	dsv_td.SampleDesc.Count = 1u;
	dsv_td.Usage = D3D11_USAGE_DEFAULT;
	dsv_td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	GFX_ASSERT(pulsar::gfx::instance().device()->CreateTexture2D(&dsv_td, NULL, &this->mp_dsv_texture));

	dsvd.Format = DXGI_FORMAT_D32_FLOAT;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	GFX_ASSERT(pulsar::gfx::instance().device()->CreateDepthStencilView(this->mp_dsv_texture, &dsvd, &this->mp_dsv));

	td.Width = width;
	td.Height = height;
	td.MipLevels = 1u;
	td.ArraySize = 6u;
	td.Format = DXGI_FORMAT_R32G32_FLOAT;
	td.SampleDesc.Count = 1u;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	td.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
	this->create_texture(&td);

	srvd.Format = DXGI_FORMAT_R32G32_FLOAT;
	srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
	srvd.TextureCube.MipLevels = 1u;
	GFX_ASSERT(pulsar::gfx::instance().device()->CreateShaderResourceView(this->mp_texture, &srvd, &this->mp_srv));

	int i = -1;
	while (++i < 6u)
	{
		rtvd.Format = DXGI_FORMAT_R32G32_FLOAT;
		rtvd.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
		rtvd.Texture2DArray.ArraySize = 1u;
		rtvd.Texture2DArray.FirstArraySlice = i;
		GFX_ASSERT(pulsar::gfx::instance().device()->CreateRenderTargetView(this->mp_texture, &rtvd, &this->mp_rtv[i]));
	}
}

void	pulsar::point_shadow_map::destroy_shadow_map()
{
	this->destroy_texture();
	if (this->mp_dsv_texture)
	{
		this->mp_dsv_texture->Release();
		this->mp_dsv_texture = NULL;
	}
	if (this->mp_dsv)
	{
		this->mp_dsv->Release();
		this->mp_dsv = NULL;
	}
	if (this->mp_srv)
	{
		this->mp_srv->Release();
		this->mp_srv = NULL;
	}

	int i = -1;
	while (++i < 6u)
	{
		if (this->mp_rtv[i])
		{
			this->mp_rtv[i]->Release();
			this->mp_rtv[i] = NULL;
		}
	}
}

void	pulsar::point_shadow_map::set(UINT width, UINT height, float z_near, float z_far)
{
	this->destroy_shadow_map();
	this->create_shadow_map(width, height);

	this->m_viewport.set(width, height);
	this->m_width = width;
	this->m_height = height;
	this->m_z_near = z_near;
	this->m_z_far = z_far;
}

void	pulsar::point_shadow_map::clear()
{
	float clear_color[3] = { FLT_MAX, FLT_MAX, FLT_MAX };	//I don't know why it requires 3 components per pixel for 2-channel texture

	int i = -1;
	while (++i < 6u)
	{
		pulsar::gfx::instance().device_context()->ClearRenderTargetView(this->mp_rtv[i], clear_color);
	}
}

uint8_t		pulsar::point_shadow_map::draw_calls() const
{
	return (6u);
}

void	pulsar::point_shadow_map::bind_rtv(uint8_t id, const pulsar::transform *transform)
{
	XMFLOAT3 pos3 = transform->get_position();
	XMVECTOR pos = XMVectorSet(pos3.x, pos3.y, pos3.z, 0.0f);

	XMVECTOR dir = XMLoadFloat3(&this->m_view_specs[id].dir);
	XMVECTOR up = XMLoadFloat3(&this->m_view_specs[id].up);
	XMMATRIX view = XMMatrixTranspose(XMMatrixLookToLH(pos, dir, up));
	XMMATRIX proj = XMMatrixTranspose(XMMatrixPerspectiveFovLH(XM_PIDIV2, 1.0f, this->m_z_near, this->m_z_far));

	XMStoreFloat4x4(&this->m_view, view);
	XMStoreFloat4x4(&this->m_proj, proj);

	this->m_view_cbuffer.update();
	this->m_proj_cbuffer.update();

	this->m_view_cbuffer.bind();
	this->m_proj_cbuffer.bind();
	this->m_viewport.bind();

	pulsar::gfx::instance().device_context()->ClearDepthStencilView(this->mp_dsv, D3D11_CLEAR_DEPTH, 1.0f, 0u);
	pulsar::gfx::instance().device_context()->OMSetRenderTargets(1u, &this->mp_rtv[id], this->mp_dsv);
}

void	pulsar::point_shadow_map::bind_srv()
{
	pulsar::gfx::instance().device_context()->PSSetShaderResources(this->m_slot, 1u, &this->mp_srv);
}

void	pulsar::point_shadow_map::unbind_rtv()
{
	pulsar::gfx::instance().device_context()->OMSetRenderTargets(0u, NULL, NULL);

	this->m_viewport.unbind();
	this->m_proj_cbuffer.bind();
	this->m_view_cbuffer.bind();
}

void	pulsar::point_shadow_map::unbind_srv()
{
	ID3D11ShaderResourceView *null[1] = { NULL };
	pulsar::gfx::instance().device_context()->PSSetShaderResources(this->m_slot, 1u, null);

}
