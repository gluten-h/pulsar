
#include "transform.h"
#include "config/config.h"


pulsar::transform	&pulsar::transform::operator=(const pulsar::transform &t)
{
	this->m_mat = t.m_mat;
	this->m_pos = t.m_pos;
	this->m_rot = t.m_rot;
	this->m_scale = t.m_scale;

	return (*this);
}

pulsar::transform::transform(const transform &t)
{
	this->m_mat = t.m_mat;
	this->m_pos = t.m_pos;
	this->m_rot = t.m_rot;
	this->m_scale = t.m_scale;

	this->init_cbuffer();
}

pulsar::transform::transform()
{
	XMMATRIX mat = XMMatrixIdentity();
	XMStoreFloat4x4(&this->m_mat, mat);

	this->init_cbuffer();
}

void	pulsar::transform::init_cbuffer()
{
	this->m_transform_cbuffer.set(&this->m_shader_transform, pulsar::CBUFFER_TYPE::DYNAMIC);
	this->m_transform_cbuffer.set_slot(pulsar::VERT_TRANSFORM_SLOT);
	this->m_transform_cbuffer.set_modified();
}

void	pulsar::transform::construct_matrix()
{
	this->m_transform_cbuffer.set_modified();

	XMVECTOR quat_vec = XMLoadFloat4(&this->m_rot);
	XMMATRIX mat = XMMatrixScaling(this->m_scale.x, this->m_scale.y, this->m_scale.z)
					* XMMatrixRotationQuaternion(quat_vec)
					* XMMatrixTranslation(this->m_pos.x, this->m_pos.y, this->m_pos.z);

	XMStoreFloat4x4(&this->m_mat, mat);
}

void	pulsar::transform::bind() const
{
	if (this->m_transform_cbuffer.is_modified())
	{
		XMMATRIX mat = XMLoadFloat4x4(&this->m_mat);
		XMMATRIX model = XMMatrixTranspose(mat);
		XMMATRIX norm = XMMatrixInverse(NULL, mat);

		XMStoreFloat4x4(&this->m_shader_transform.model, model);
		XMStoreFloat4x4(&this->m_shader_transform.norm, norm);

		this->m_transform_cbuffer.update();
	}
	this->m_transform_cbuffer.bind();
}

void	pulsar::transform::unbind() const
{
	this->m_transform_cbuffer.unbind();
}
