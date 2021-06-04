#pragma once

#include "igrng_d3d.h"
#include "grng_scene_def.h"


enum GRNG_LIGHT_TYPE
{
	GRNG_LIGHT_TYPE_POINT,
	GRNG_LIGHT_TYPE_DIR
};


typedef struct			grng_shader_light
{
	int					type;
	float				pd0[3];

	XMFLOAT3			pos;
	float				pd1[1];

	XMFLOAT3			dir;
	float				pd2[1];

	XMFLOAT3			color;
	float				pd3[1];

	XMFLOAT4			attenuation;
}						GRNG_SHADER_LIGHT;


typedef struct			grgn_shader_light_scene
{
	int					light_count;
	int					pd0[3];

	GRNG_SHADER_LIGHT	light[GRNG_MAX_LIGHT_COUNT];
}						GRNG_SHADER_LIGHT_SCENE;


class grng_light : public IGRNG_D3D
{
protected:
	int			type = -1;

public:
	grng_light() : IGRNG_D3D(){ }

	virtual void		set_shader_light(GRNG_SHADER_LIGHT &sl) = 0;
};

using GRNG_LIGHT = grng_light;
