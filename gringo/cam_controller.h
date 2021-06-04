#pragma once


typedef struct		grng_cam_controller
{
	float			movement_speed = 0.0f;
	float			lift_speed = 0.0f;
	float			rotation_speed = 0.0f;
}					GRNG_CAM_CONTROLLER;


void		grng_cam_controller(void *data);
