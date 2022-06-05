
#include "transform.h"


const XMMATRIX	&pulsar::transform::get_matrix() const
{
	return (this->m_mat);
}

const XMFLOAT3	&pulsar::transform::get_position() const
{
	return (this->m_pos);
}

const XMFLOAT3	&pulsar::transform::get_rotation() const
{
	return (this->m_rot);
}

const XMFLOAT3	&pulsar::transform::get_scale() const
{
	return (this->m_scale);
}


void	pulsar::transform::set_position(const XMVECTOR &pos)
{
	this->m_pos = XMFLOAT3(XMVectorGetX(pos), XMVectorGetY(pos), XMVectorGetZ(pos));
	this->construct_matrix();
}

void	pulsar::transform::set_position(const XMFLOAT3 &pos)
{
	this->m_pos = pos;
	this->construct_matrix();
}

void	pulsar::transform::set_rotation(const XMVECTOR &rot)
{
	this->m_rot = XMFLOAT3(XMVectorGetX(rot), XMVectorGetY(rot), XMVectorGetZ(rot));
	this->construct_matrix();
}

void	pulsar::transform::set_rotation(const XMFLOAT3 &rot)
{
	this->m_rot = rot;
	this->construct_matrix();
}

void	pulsar::transform::set_scale(const XMVECTOR &scale)
{
	this->m_scale = XMFLOAT3(XMVectorGetX(scale), XMVectorGetY(scale), XMVectorGetZ(scale));
	this->construct_matrix();
}

void	pulsar::transform::set_scale(const XMFLOAT3 &scale)
{
	this->m_scale = scale;
	this->construct_matrix();
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
