#pragma once

#include "grng_math.h"


typedef struct		grng_cam_controller
{
	float			movement_speed = 0.0f;
	float			lift_speed = 0.0f;
	float			rotation_speed = 0.0f;
	float			rotation_sharpness = 1.0f;

	XMFLOAT2		last_rot = { 0,0 };
	XMINT2			last_pressed_pos = { 0,0 };
	bool			is_cursor_hidden = false;
}					GRNG_CAM_CONTROLLER;


void		grng_cam_controller(void *data);
