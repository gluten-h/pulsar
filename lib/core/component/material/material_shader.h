#pragma once

#include "pulsar_id3d.h"
#include "material_def.h"


namespace PULSAR
{
	struct		MATERIAL_SHADER
	{
		XMFLOAT3	albedo_color = XMFLOAT3(1.0f, 1.0f, 1.0f);
		bool	albedo_map_srgb;

		float	normal_factor = 1.0f;
		float	pd1[3];

		float	roughness = 1.0f;
		float	pd2[3];

		float	metalness = 1.0f;
		float	pd3[3];

		float	ao = 1.0f;
		float	pd4[3];

		float	exposure = 1.0f;
		float	pd5[3];
	};
}
