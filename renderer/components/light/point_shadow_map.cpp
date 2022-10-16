
#include "point_shadow_map.h"
#include "exceptions/gfx_exception.h"
#include "config/config.h"
#include "transform/transform.h"
#include "shadow_atlas.h"
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
	int i = -1;
	while (++i < 6u)
	{
		this->m_rects[i] = pulsar::shadow_atlas::instance().insert(width, height);
		this->m_viewports[i].set(&this->m_rects[i]);

		this->m_uvs[i] = { (float)this->m_rects[i].left / (float)pulsar::SHADOW_ATLAS_SIZE.x,
							(float)this->m_rects[i].top / (float)pulsar::SHADOW_ATLAS_SIZE.y,
							(float)this->m_rects[i].right / (float)pulsar::SHADOW_ATLAS_SIZE.x,
							(float)this->m_rects[i].bottom / (float)pulsar::SHADOW_ATLAS_SIZE.y };
	}
}

void	pulsar::point_shadow_map::destroy_shadow_map()
{
	//int i = -1;
	//while (++i < 6u)
	//{
	//	pulsar::shadow_atlas::instance().free(this->m_rects[i]);
	//}
}

void	pulsar::point_shadow_map::set(UINT width, UINT height, float z_near, float z_far)
{
	assert(("Invalid size", width == height));

	this->destroy_shadow_map();
	this->create_shadow_map(width, height);

	this->m_z_near = z_near;
	this->m_z_far = z_far;
}

void	pulsar::point_shadow_map::clear()
{
	int i = -1;
	while (++i < 6u)
	{
		pulsar::shadow_atlas::instance().clear(&this->m_rects[i]);
	}
}

uint8_t		pulsar::point_shadow_map::draw_calls() const
{
	return (6u);
}

XMFLOAT4	pulsar::point_shadow_map::uv(uint8_t id) const
{
	return (this->m_uvs[id]);
}

void	pulsar::point_shadow_map::bind_rtv(uint8_t id, const pulsar::transform *transform)
{
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
	}

	this->m_viewports[id].bind();
	pulsar::gfx::instance().device_context()->RSSetScissorRects(1u, &this->m_rects[id]);
	pulsar::shadow_atlas::instance().bind_rtv();
}

void	pulsar::point_shadow_map::bind_srv()
{
	pulsar::shadow_atlas::instance().bind_srv();
}

void	pulsar::point_shadow_map::unbind_rtv()
{
	pulsar::shadow_atlas::instance().unbind_rtv();

	this->m_viewports[0].unbind();
	this->m_proj_cbuffer.unbind();
	this->m_view_cbuffer.unbind();
}

void	pulsar::point_shadow_map::unbind_srv()
{
	pulsar::shadow_atlas::instance().unbind_srv();
}
