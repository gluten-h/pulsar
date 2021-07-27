
#include "grng_camera.h"


GRNG_COMPONENT		*grng_camera::create_manager_ptr()
{
	grng_camera	*cam = new grng_camera;

	return (cam);
}

void				grng_camera::set(const GRNG_TRANSFORM &transform, float fov_rad, float z_near, float z_far, float exposure, float gamma)
{
	this->transform = transform;
	this->update_view_matrix();

	this->fov_rad = fov_rad;
	this->z_near = z_near;
	this->z_far = z_far;

	this->exposure = exposure;
	this->gamma = gamma;

	grng_camera::cam_deferred_cbuffer.set_slot(GRNG_DEFERRED_CAM_SLOT);
}

void				grng_camera::set_z_near(float z_near)
{
	this->z_near = z_near;
}

void				grng_camera::set_z_far(float z_far)
{
	this->z_far = z_far;
}

void				grng_camera::set_exposure(float exposure)
{
	this->exposure = exposure;
}

void				grng_camera::set_gamma(float gamma)
{
	this->gamma = gamma;
}
