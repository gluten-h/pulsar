#pragma once

#include "igrng_d3d.h"


class grng_component_transform
{
private:
	XMMATRIX	transform_mat = XMMatrixIdentity();
	
public:
	XMFLOAT3	position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3	rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3	scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

public:
	grng_component_transform(){ }
	grng_component_transform(const XMFLOAT3 &position, const XMFLOAT3 &rotation, const XMFLOAT3 &scale)
	{
		this->position = position;
		this->rotation = rotation;
		this->scale = scale;
	}

	void	update_transform_matrix()
	{
		/*this->transform_mat = XMMatrixTranspose(XMMatrixScaling(this->scale.x, this->scale.y, this->scale.z)
												* XMMatrixRotationRollPitchYaw(this->rotation.x, this->rotation.y, this->rotation.z)
												* XMMatrixTranslation(this->position.x, this->position.y, this->position.z));*/
		this->transform_mat = XMMatrixScaling(this->scale.x, this->scale.y, this->scale.z)
												* XMMatrixRotationRollPitchYaw(this->rotation.x, this->rotation.y, this->rotation.z)
												* XMMatrixTranslation(this->position.x, this->position.y, this->position.z);
	}


	const XMMATRIX		&get_transform_matrix()
	{
		return (this->transform_mat);
	}
};

using GRNG_COMPONENT_TRANSFORM = grng_component_transform;
