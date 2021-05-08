#pragma once

#include "grng_components.h"


class grng_gfx
{
private:
	static GRNG_CAMERA		*curr_camera;

public:
	static void					set_camera(GRNG_CAMERA *cam)
	{
		grng_gfx::curr_camera = cam;
	}

	static const GRNG_CAMERA	&get_camera()
	{
		return (*grng_gfx::curr_camera);
	}
};

using GRNG_GFX = grng_gfx;
