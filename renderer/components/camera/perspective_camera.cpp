
#include "perspective_camera.h"


pulsar::perspective_camera::perspective_camera(UINT width, UINT height, float fov_rad, float z_near, float z_far) : pulsar::camera(width, height)
{
	this->m_fov_rad = fov_rad;
	this->m_z_near = z_near;
	this->m_z_far = z_far;

	XMMATRIX mat = XMMatrixPerspectiveFovLH(this->m_fov_rad, (float)width / (float)height, this->m_z_near, this->m_z_far);
	XMStoreFloat4x4(&this->m_mat, mat);
}

