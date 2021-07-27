#pragma once

#include "grng_id3d.h"


typedef struct			grng_camera_deferred_shader
{
	XMFLOAT3			pos;
	float				pd0;

	XMFLOAT3			dir;
	float				pd1;

	float				gamma;
	float				pd2[3];
}						GRNG_CAMERA_DEFERRED_SHADER;
