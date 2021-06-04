#pragma once

#include "igrng_d3d.h"


typedef struct			grng_shader_camera
{
	XMFLOAT3			cam_pos;
	float				pd0;

	XMFLOAT3			cam_dir;
	float				pd1;
}						GRNG_SHADER_CAMERA;
