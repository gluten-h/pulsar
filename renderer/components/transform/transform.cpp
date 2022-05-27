
#include "transform.h"
#include "config/config.h"


pulsar::transform	&pulsar::transform::operator=(const pulsar::transform &t)
{
	this->set_matrix(t.m_mat);
	return (*this);
}

pulsar::transform::transform(const transform &t)
{
	this->set_matrix(t.m_mat);
	this->init_cbuffer();
}

pulsar::transform::transform()
{
	this->init_cbuffer();
}

void	pulsar::transform::init_cbuffer()
{
	this->m_transform_cbuffer.set_data(this->m_shader_transform);
	this->m_transform_cbuffer.set_slot(pulsar::G_BUFFER_VERT_TRANSFORM_SLOT);
	this->m_transform_cbuffer.set_modified();
}

const XMMATRIX	&pulsar::transform::get_matrix() const
{
	return (this->m_mat);
}

void	pulsar::transform::set_matrix(const XMMATRIX &matrix)
{
	this->m_transform_cbuffer.set_modified();
	this->m_mat = matrix;
}

XMFLOAT3	pulsar::transform::get_position() const
{
	XMVECTOR vec = this->m_mat.r[3];
	return (XMFLOAT3(XMVectorGetX(vec), XMVectorGetY(vec), XMVectorGetZ(vec)));
}

void	pulsar::transform::set_position(const XMFLOAT3 &pos)
{
	this->m_transform_cbuffer.set_modified();
	this->m_mat.r[3] = XMVectorSet(pos.x, pos.y, pos.z, 1.0f);
}

XMFLOAT3	pulsar::transform::forward() const
{
	XMVECTOR vec = XMVector3Normalize(this->m_mat.r[2]);
	return (XMFLOAT3(XMVectorGetX(vec), XMVectorGetY(vec), XMVectorGetZ(vec)));
}

XMFLOAT3	pulsar::transform::right() const
{
	XMVECTOR vec = XMVector3Normalize(this->m_mat.r[0]);
	return (XMFLOAT3(XMVectorGetX(vec), XMVectorGetY(vec), XMVectorGetZ(vec)));
}

XMFLOAT3	pulsar::transform::up() const
{
	XMVECTOR vec = XMVector3Normalize(this->m_mat.r[1]);
	return (XMFLOAT3(XMVectorGetX(vec), XMVectorGetY(vec), XMVectorGetZ(vec)));
}

void	pulsar::transform::bind() const
{
	if (this->m_transform_cbuffer.is_modified())
	{
		this->m_shader_transform.model = XMMatrixTranspose(this->m_mat);
		this->m_shader_transform.norm = XMMatrixTranspose(XMMatrixInverse(NULL, this->m_mat));

		this->m_transform_cbuffer.update();
	}
	this->m_transform_cbuffer.bind();
}

void	pulsar::transform::unbind() const
{
	this->m_transform_cbuffer.unbind();
}
