
#include "camera.h"


pulsar::camera::camera(UINT width, UINT height)
{
	this->m_viewport.set(width, height);
}

pulsar::viewport	&pulsar::camera::viewport()
{
	return (this->m_viewport);
}

const XMFLOAT4X4	&pulsar::camera::projection() const
{
	return (this->m_mat);
}
