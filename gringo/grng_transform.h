#pragma once

#include "grng_transform_shader.h"
#include "grng_vert_const_buffer.h"


class grng_transform
{
private:
	friend class grng_camera;

private:
	XMMATRIX			transform_matrix = XMMatrixIdentity();
	static XMMATRIX		cam_view_matrix;
	static XMMATRIX		cam_proj_matrix;

	static GRNG_TRANSFORM_SHADER							transform_shader;
	static GRNG_VERT_CONST_BUFFER<GRNG_TRANSFORM_SHADER>	transform_cbuffer;


	void		update_transform_matrix()
	{
		this->transform_matrix = XMMatrixScaling(this->scale.x, this->scale.y, this->scale.z)
			* XMMatrixRotationRollPitchYaw(this->rotation.x, this->rotation.y, this->rotation.z)
			* XMMatrixTranslation(this->position.x, this->position.y, this->position.z);
	}
	
public:
	XMFLOAT3	position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3	rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3	scale = XMFLOAT3(1.0f, 1.0f, 1.0f);


	grng_transform		&operator=(const grng_transform &t)
	{
		this->transform_matrix = t.transform_matrix;
		this->position = t.position;
		this->rotation = t.rotation;
		this->scale = t.scale;

		return (*this);
	}
	grng_transform(const grng_transform &t)
	{
		this->transform_matrix = t.transform_matrix;
		this->position = t.position;
		this->rotation = t.rotation;
		this->scale = t.scale;
	}
	grng_transform(){ }
	grng_transform(const XMFLOAT3 &position, const XMFLOAT3 &rotation, const XMFLOAT3 &scale)
	{
		this->position = position;
		this->rotation = rotation;
		this->scale = scale;
	}

	void		bind(GRNG_BIND_SCOPE scope)
	{
		this->update_transform_matrix();
		grng_transform::transform_shader.model = this->transform_matrix;
		grng_transform::transform_shader.view = grng_transform::cam_view_matrix;
		grng_transform::transform_shader.proj = grng_transform::cam_proj_matrix;
		grng_transform::transform_shader.norm = XMMatrixTranspose(XMMatrixInverse(NULL, this->transform_matrix));

		grng_transform::transform_cbuffer.update(grng_transform::transform_shader);
		grng_transform::transform_cbuffer.bind(scope);
	}


	const XMMATRIX		&get_transform_matrix()
	{
		return (this->transform_matrix);
	}
};

using GRNG_TRANSFORM = grng_transform;
