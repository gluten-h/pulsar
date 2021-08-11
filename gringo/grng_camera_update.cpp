
#include "grng_camera.h"


void		grng_camera::update_view_matrix()
{
	this->transform.scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	this->transform.update_transform_matrix();

	XMMATRIX transform_mat = this->transform.get_transform_matrix();

	XMVECTOR forward_vec = XMVector3NormalizeEst(transform_mat.r[2]);
	XMVECTOR right_vec = XMVector3NormalizeEst(transform_mat.r[0]);
	XMVECTOR up_vec = XMVector3NormalizeEst(transform_mat.r[1]);

	this->forward = XMFLOAT3(XMVectorGetX(forward_vec), XMVectorGetY(forward_vec), XMVectorGetZ(forward_vec));
	this->right = XMFLOAT3(XMVectorGetX(right_vec), XMVectorGetY(right_vec), XMVectorGetZ(right_vec));
	this->up = XMFLOAT3(XMVectorGetX(up_vec), XMVectorGetY(up_vec), XMVectorGetZ(up_vec));

	this->view_matrix = XMMatrixLookAtLH(transform_mat.r[3], transform_mat.r[3] + forward_vec, up_vec);
}

void		grng_camera::update_proj_matrix(float w, float h)
{
	this->proj_matrix = XMMatrixPerspectiveFovLH(this->fov_rad, (float)w / (float)h, this->z_near, this->z_far);
}


void		grng_camera::update_camera_deferred_shader(GRNG_BIND_SCOPE scope)
{
	grng_camera::cam_deferred_shader.pos = this->transform.position;
	grng_camera::cam_deferred_shader.dir = this->forward;
	grng_camera::cam_deferred_shader.gamma = this->gamma;

	grng_camera::cam_deferred_cbuffer.update(grng_camera::cam_deferred_shader);
	grng_camera::cam_deferred_cbuffer.bind(scope);
}

void		grng_camera::update_camera_post_effects_shader(GRNG_BIND_SCOPE scope)
{
	grng_camera::cam_post_effects_shader.gamma = this->gamma;
	grng_camera::cam_post_effects_shader.exposure = this->exposure;

	grng_camera::cam_post_effects_cbuffer.update(grng_camera::cam_post_effects_shader);
	grng_camera::cam_post_effects_cbuffer.bind(scope);
}

void		grng_camera::update(float w, float h)
{
	this->update_view_matrix();
	this->update_proj_matrix(w, h);

	GRNG_TRANSFORM::cam_view_matrix = this->view_matrix;
	GRNG_TRANSFORM::cam_proj_matrix = this->proj_matrix;
}
