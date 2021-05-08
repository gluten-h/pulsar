#pragma once

#include "grng_component_transform.h"

class grng_camera
{
private:
	GRNG_COMPONENT_TRANSFORM	transform;
	XMFLOAT3					forward = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3					right = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3					up = XMFLOAT3(0.0f, 0.0f, 0.0f);

	XMMATRIX					view_matrix = XMMatrixIdentity();
	XMMATRIX					proj_matrix = XMMatrixIdentity();

	float fov_rad = 0.0f;
	float z_near = 0.0f;
	float z_far = 0.0f;


	void		update_view_matrix()
	{
		this->transform.scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
		this->transform.update_transform_matrix();

		//XMMATRIX transform_mat = XMMatrixTranspose(this->transform.get_transform_matrix());
		XMMATRIX transform_mat = this->transform.get_transform_matrix();

		XMVECTOR forward_vec = XMVector3NormalizeEst(transform_mat.r[2]);
		XMVECTOR right_vec = XMVector3NormalizeEst(XMVector3Cross(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), forward_vec));
		XMVECTOR up_vec = XMVector3NormalizeEst(XMVector3Cross(forward_vec, right_vec));

		this->forward = XMFLOAT3(XMVectorGetX(forward_vec), XMVectorGetY(forward_vec), XMVectorGetZ(forward_vec));
		this->right = XMFLOAT3(XMVectorGetX(right_vec), XMVectorGetY(right_vec), XMVectorGetZ(right_vec));
		this->up = XMFLOAT3(XMVectorGetX(up_vec), XMVectorGetY(up_vec), XMVectorGetZ(up_vec));
		
		//this->view_matrix = XMMatrixTranspose(XMMatrixLookAtLH(transform_mat.r[3], transform_mat.r[3] + forward_vec, up_vec));
		this->view_matrix = XMMatrixLookAtLH(transform_mat.r[3], transform_mat.r[3] + forward_vec, up_vec);
	}

	void		update_proj_matrix(float w, float h)
	{
		//this->proj_matrix = XMMatrixTranspose(XMMatrixPerspectiveFovLH(this->fov_rad, (float)w / (float)h, this->z_near, this->z_far));
		this->proj_matrix = XMMatrixPerspectiveFovLH(this->fov_rad, (float)w / (float)h, this->z_near, this->z_far);
	}

public:
	grng_camera(const GRNG_COMPONENT_TRANSFORM &transform, float fov_rad, float z_near, float z_far)
	{
		this->transform = transform;
		this->update_view_matrix();

		this->fov_rad = fov_rad;
		this->z_near = z_near;
		this->z_far = z_far;
	}

	void	update(float w, float h)
	{
		this->update_view_matrix();
		this->update_proj_matrix(w, h);
	}


	const XMMATRIX		&get_view_matrix() const
	{
		return (this->view_matrix);
	}

	const XMMATRIX		&get_proj_matrix() const
	{
		return (this->proj_matrix);
	}
};

using GRNG_CAMERA = grng_camera;
