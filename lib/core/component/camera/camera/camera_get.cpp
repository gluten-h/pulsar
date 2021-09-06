
#include "camera.h"


const XMMATRIX		&PULSAR::CAMERA::get_view_matrix() const
{
	return (this->view_matrix);
}

const XMMATRIX		&PULSAR::CAMERA::get_proj_matrix() const
{
	return (this->proj_matrix);
}

const XMFLOAT3		&PULSAR::CAMERA::get_position() const
{
	return (this->transform.position);
}

const XMFLOAT3		&PULSAR::CAMERA::get_forward() const
{
	return (this->forward);
}

const XMFLOAT3		&PULSAR::CAMERA::get_right() const
{
	return (this->right);
}

const XMFLOAT3		&PULSAR::CAMERA::get_up() const
{
	return (this->up);
}

PULSAR::TRANSFORM		&PULSAR::CAMERA::get_transform()
{
	return (this->transform);
}

float		PULSAR::CAMERA::get_z_near() const
{
	return (this->z_near);
}

float		PULSAR::CAMERA::get_z_far() const
{
	return (this->z_far);
}

float		PULSAR::CAMERA::get_gamma() const
{
	return (this->gamma);
}
