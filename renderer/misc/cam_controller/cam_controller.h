#pragma once

#include "pulsar_math.h"
#include "gfx.h"
#include "pulsar_input.h"
#include "window.h"


struct		CAM_CONTROLLER_DATA
{
	float		movement_speed = 0.0f;
	float		lift_speed = 0.0f;
	float		rotation_speed = 0.0f;
	float		rotation_sharpness = 1.0f;

	XMFLOAT2	last_rot = { 0,0 };
	XMINT2		last_pressed_pos = { 0,0 };
	bool		is_cursor_hidden = false;
};


void		cam_controller(void *data);
