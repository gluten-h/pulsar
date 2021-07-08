#pragma once

#include "grng_id3d.h"


struct grng_shader_transform
{
	XMMATRIX		model = XMMatrixIdentity();
	XMMATRIX		view = XMMatrixIdentity();
	XMMATRIX		proj = XMMatrixIdentity();
	XMMATRIX		norm = XMMatrixIdentity();
};

using GRNG_SHADER_TRANSFORM = grng_shader_transform;
