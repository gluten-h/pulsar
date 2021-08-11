
#include "grng_camera.h"


grng_camera			*grng_camera::create()
{
	grng_camera *camera = new grng_camera;
	camera->id = GRNG_CM.add(camera);
	if (camera->id == -1)
	{
		delete camera;
		return (NULL);
	}
	camera->is_alloc = true;

	return (camera);
}

void				grng_camera::set(const GRNG_TRANSFORM &transform, float fov_rad, float exposure, float gamma, float z_near, float z_far)
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
