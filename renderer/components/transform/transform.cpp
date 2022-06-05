
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
	this->init_cbuffer();
}

void	pulsar::transform::init_cbuffer()
{
	this->m_transform_cbuffer.set_data(this->m_shader_transform);
	this->m_transform_cbuffer.set_slot(pulsar::G_BUFFER_VERT_TRANSFORM_SLOT);
	this->m_transform_cbuffer.set_modified();
}

void	pulsar::transform::construct_matrix()
{
	this->m_transform_cbuffer.set_modified();

	this->m_mat = XMMatrixScaling(this->m_scale.x, this->m_scale.y, this->m_scale.z)
		* XMMatrixRotationRollPitchYaw(this->m_rot.x, this->m_rot.y, this->m_rot.z)
		* XMMatrixTranslation(this->m_pos.x, this->m_pos.y, this->m_pos.z);
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
