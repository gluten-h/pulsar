#pragma once

#include "pulsar_id3d.h"
#include "def_scene.h"


namespace PULSAR
{
	struct		SHADER_LIGHT
	{
		int			type;
		float		pd0[3];

		XMFLOAT3	pos;
		float		pd1[1];

		XMFLOAT3	dir;
		float		pd2[1];

		XMFLOAT3	color;
		float		pd3[1];

		XMFLOAT4	attenuation;
	};


	struct		SHADER_LIGHT_SCENE
	{
		int		light_count;
		int		pd0[3];

		PULSAR::SHADER_LIGHT	light[PULSAR::MAX_LIGHT_COUNT];
	};
}
