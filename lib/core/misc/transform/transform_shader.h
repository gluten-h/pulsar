#pragma once

#include "pulsar_id3d.h"


namespace PULSAR
{
	struct		TRANSFORM_SHADER
	{
		XMMATRIX	model = XMMatrixIdentity();
		XMMATRIX	view = XMMatrixIdentity();
		XMMATRIX	proj = XMMatrixIdentity();
		XMMATRIX	norm = XMMatrixIdentity();
	};
}
