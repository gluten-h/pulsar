
#include "perspective_camera.h"


pulsar::perspective_camera::perspective_camera(UINT width, UINT height, float fov_rad, float z_near, float z_far) : pulsar::camera(width, height)
{
	this->m_fov_rad = fov_rad;
	this->m_z_near = z_near;
	this->m_z_far = z_far;
}

const XMMATRIX	&pulsar::perspective_camera::get_projection() const
{
	XMUINT2 viewport_size = this->m_viewport.size();
	return (XMMatrixPerspectiveFovLH(this->m_fov_rad, (float)viewport_size.x / (float)viewport_size.y, this->m_z_near, this->m_z_far));
}

