#pragma once

#include "pulsar_id3d.h"


namespace PULSAR
{
	struct		CAMERA_DEFERRED_SHADER
	{
		XMFLOAT3	pos;
		float		pd0;

		XMFLOAT3	dir;
		float		pd1;

		float		gamma;
		float		pd2[3];
	};
}
