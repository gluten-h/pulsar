
#include "grng_camera.h"


void			grng_camera::copy_assign(const grng_camera &c)
{
	this->transform = c.transform;
	this->forward = c.forward;
	this->right = c.right;
	this->up = c.up;

	this->view_matrix = c.view_matrix;
	this->proj_matrix = c.proj_matrix;

	this->fov_rad = c.fov_rad;
	this->z_near = c.z_near;
	this->z_far = c.z_far;

	this->exposure = c.exposure;
	this->gamma = c.gamma;
}


grng_camera		&grng_camera::operator=(const grng_camera &c)
{
	this->copy_assign(c);

	return (*this);
}

grng_camera::grng_camera(const grng_camera &c) : GRNG_COMPONENT()
{
	this->type = GRNG_COMPONENT_TYPE::CAMERA;
	this->copy_assign(c);

}

grng_camera::grng_camera() : GRNG_COMPONENT()
{
	this->type = GRNG_COMPONENT_TYPE::CAMERA;
}

grng_camera::grng_camera(const GRNG_TRANSFORM &transform, float fov_rad, float z_near, float z_far, float exposure, float gamma) : GRNG_COMPONENT()
{
	this->type = GRNG_COMPONENT_TYPE::CAMERA;
	this->set(transform, fov_rad, z_near, z_far, exposure, gamma);
}
