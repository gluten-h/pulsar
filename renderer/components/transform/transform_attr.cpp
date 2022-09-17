
#include "transform.h"


const XMFLOAT4X4	&pulsar::transform::get_matrix() const
{
	return (this->m_mat);
}

const XMFLOAT3	&pulsar::transform::get_position() const
{
	return (this->m_pos);
}

const XMFLOAT4	&pulsar::transform::get_rotation() const
{
	return (this->m_rot);
}

const XMFLOAT3	&pulsar::transform::get_scale() const
{
	return (this->m_scale);
}


void	pulsar::transform::set_position(const XMFLOAT3 &pos)
{
	this->m_pos = pos;
	this->construct_matrix();
}

void	pulsar::transform::set_rotation(const XMFLOAT4 &rot)
{
	this->m_rot = rot;
	this->construct_matrix();
}

void	pulsar::transform::set_rotation(float pitch, float yaw, float roll)
{
	XMVECTOR rot = XMQuaternionRotationRollPitchYaw(pitch, yaw, roll);
	XMStoreFloat4(&this->m_rot, rot);
	this->construct_matrix();
}

void	pulsar::transform::set_scale(const XMFLOAT3 &scale)
{
	this->m_scale = scale;
	this->construct_matrix();
}


XMFLOAT3	pulsar::transform::forward() const
{
	XMFLOAT3 vec_f3;
	XMVECTOR vec = XMVectorSet(this->m_mat._31, this->m_mat._32, this->m_mat._33, 0.0f);
	vec = XMVector3Normalize(vec);
	XMStoreFloat3(&vec_f3, vec);

	return (vec_f3);
}

XMFLOAT3	pulsar::transform::right() const
{
	XMFLOAT3 vec_f3;
	XMVECTOR vec = XMVectorSet(this->m_mat._11, this->m_mat._12, this->m_mat._13, 0.0f);
	vec = XMVector3Normalize(vec);
	XMStoreFloat3(&vec_f3, vec);

	return (vec_f3);
}

XMFLOAT3	pulsar::transform::up() const
{
	XMFLOAT3 vec_f3;
	XMVECTOR vec = XMVectorSet(this->m_mat._21, this->m_mat._22, this->m_mat._23, 0.0f);
	vec = XMVector3Normalize(vec);
	XMStoreFloat3(&vec_f3, vec);

	return (vec_f3);
}
