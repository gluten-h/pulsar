
#include "grng_camera.h"


const XMMATRIX			&grng_camera::get_view_matrix() const
{
	return (this->view_matrix);
}

const XMMATRIX			&grng_camera::get_proj_matrix() const
{
	return (this->proj_matrix);
}

const XMFLOAT3			&grng_camera::get_position() const
{
	return (this->transform.position);
}

const XMFLOAT3			&grng_camera::get_forward() const
{
	return (this->forward);
}

const XMFLOAT3			&grng_camera::get_right() const
{
	return (this->right);
}

const XMFLOAT3			&grng_camera::get_up() const
{
	return (this->up);
}

GRNG_TRANSFORM			&grng_camera::get_transform()
{
	return (this->transform);
}

float					grng_camera::get_z_near() const
{
	return (this->z_near);
}

float					grng_camera::get_z_far() const
{
	return (this->z_far);
}

float					grng_camera::get_gamma() const
{
	return (this->gamma);
}
