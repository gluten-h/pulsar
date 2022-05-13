//
//#include "camera.h"
//
//
//PULSAR::CAMERA		*PULSAR::CAMERA::create()
//{
//	return ((PULSAR::CAMERA*)PULSAR::COMPONENT::add_to_manager(new PULSAR::CAMERA));
//}
//
//void		PULSAR::CAMERA::set(const PULSAR::TRANSFORM &transform, float fov_rad, float exposure, float gamma, float z_near, float z_far)
//{
//	this->transform = transform;
//	this->update_view_matrix();
//
//	this->fov_rad = fov_rad;
//	this->z_near = z_near;
//	this->z_far = z_far;
//
//	this->exposure = exposure;
//	this->gamma = gamma;
//
//	PULSAR::CAMERA::cam_deferred_cbuffer.set_slot(DEFERRED_CAM_SLOT);
//}
//
//void		PULSAR::CAMERA::set_z_near(float z_near)
//{
//	this->z_near = z_near;
//}
//
//void		PULSAR::CAMERA::set_z_far(float z_far)
//{
//	this->z_far = z_far;
//}
//
//void		PULSAR::CAMERA::set_exposure(float exposure)
//{
//	this->exposure = exposure;
//}
//
//void		PULSAR::CAMERA::set_gamma(float gamma)
//{
//	this->gamma = gamma;
//}
