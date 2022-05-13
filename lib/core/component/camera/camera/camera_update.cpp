//
//#include "camera.h"
//
//
//void		PULSAR::CAMERA::update_view_matrix()
//{
//	this->transform.scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
//	this->transform.update_transform_matrix();
//
//	XMMATRIX transform_mat = this->transform.get_transform_matrix();
//
//	XMVECTOR forward_vec = XMVector3NormalizeEst(transform_mat.r[2]);
//	XMVECTOR right_vec = XMVector3NormalizeEst(transform_mat.r[0]);
//	XMVECTOR up_vec = XMVector3NormalizeEst(transform_mat.r[1]);
//
//	this->forward = XMFLOAT3(XMVectorGetX(forward_vec), XMVectorGetY(forward_vec), XMVectorGetZ(forward_vec));
//	this->right = XMFLOAT3(XMVectorGetX(right_vec), XMVectorGetY(right_vec), XMVectorGetZ(right_vec));
//	this->up = XMFLOAT3(XMVectorGetX(up_vec), XMVectorGetY(up_vec), XMVectorGetZ(up_vec));
//
//	this->view_matrix = XMMatrixLookAtLH(transform_mat.r[3], transform_mat.r[3] + forward_vec, up_vec);
//}
//
//void		PULSAR::CAMERA::update_proj_matrix(float w, float h)
//{
//	this->proj_matrix = XMMatrixPerspectiveFovLH(this->fov_rad, (float)w / (float)h, this->z_near, this->z_far);
//}
//
//
//void		PULSAR::CAMERA::update_camera_deferred_shader(BIND_SCOPE scope)
//{
//	PULSAR::CAMERA::cam_deferred_shader.pos = this->transform.position;
//	PULSAR::CAMERA::cam_deferred_shader.dir = this->forward;
//	PULSAR::CAMERA::cam_deferred_shader.gamma = this->gamma;
//
//	PULSAR::CAMERA::cam_deferred_cbuffer.update(PULSAR::CAMERA::cam_deferred_shader);
//	PULSAR::CAMERA::cam_deferred_cbuffer.bind(scope);
//}
//
//void		PULSAR::CAMERA::update_camera_post_effects_shader(PULSAR::BIND_SCOPE scope)
//{
//	PULSAR::CAMERA::cam_post_effects_shader.gamma = this->gamma;
//	PULSAR::CAMERA::cam_post_effects_shader.exposure = this->exposure;
//
//	PULSAR::CAMERA::cam_post_effects_cbuffer.update(PULSAR::CAMERA::cam_post_effects_shader);
//	PULSAR::CAMERA::cam_post_effects_cbuffer.bind(scope);
//}
//
//void		PULSAR::CAMERA::update(float w, float h)
//{
//	this->update_view_matrix();
//	this->update_proj_matrix(w, h);
//
//	PULSAR::TRANSFORM::cam_view_matrix = this->view_matrix;
//	PULSAR::TRANSFORM::cam_proj_matrix = this->proj_matrix;
//}
