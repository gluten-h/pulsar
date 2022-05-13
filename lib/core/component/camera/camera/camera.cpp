//
//#include "camera.h"
//
//
//void		PULSAR::CAMERA::copy_assign(const CAMERA &c)
//{
//	this->transform = c.transform;
//	this->forward = c.forward;
//	this->right = c.right;
//	this->up = c.up;
//
//	this->view_matrix = c.view_matrix;
//	this->proj_matrix = c.proj_matrix;
//
//	this->fov_rad = c.fov_rad;
//	this->z_near = c.z_near;
//	this->z_far = c.z_far;
//
//	this->exposure = c.exposure;
//	this->gamma = c.gamma;
//}
//
//
//PULSAR::CAMERA		&PULSAR::CAMERA::operator=(const CAMERA &c)
//{
//	this->copy_assign(c);
//
//	return (*this);
//}
//
//PULSAR::CAMERA::CAMERA(const CAMERA &c) : PULSAR::COMPONENT()
//{
//	this->type = PULSAR::COMPONENT_TYPE::CAMERA;
//	this->copy_assign(c);
//
//}
//
//PULSAR::CAMERA::CAMERA() : PULSAR::COMPONENT()
//{
//	this->type = PULSAR::COMPONENT_TYPE::CAMERA;
//}
//
//PULSAR::CAMERA::CAMERA(const PULSAR::TRANSFORM &transform, float fov_rad, float z_near, float z_far, float exposure, float gamma) : PULSAR::COMPONENT()
//{
//	this->type = PULSAR::COMPONENT_TYPE::CAMERA;
//	this->set(transform, fov_rad, z_near, z_far, exposure, gamma);
//}
