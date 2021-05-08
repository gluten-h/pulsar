#pragma once

#include "igrng_d3d.h"


struct grng_vert_transform
{
	XMMATRIX		world = XMMatrixIdentity();
	XMMATRIX		view = XMMatrixIdentity();
	XMMATRIX		proj = XMMatrixIdentity();
};

using GRNG_VERT_TRANSFORM = grng_vert_transform;
