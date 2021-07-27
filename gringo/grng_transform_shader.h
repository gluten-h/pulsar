#pragma once

#include "grng_id3d.h"


struct grng_transform_shader
{
	XMMATRIX		model = XMMatrixIdentity();
	XMMATRIX		view = XMMatrixIdentity();
	XMMATRIX		proj = XMMatrixIdentity();
	XMMATRIX		norm = XMMatrixIdentity();
};

using GRNG_TRANSFORM_SHADER = grng_transform_shader;
