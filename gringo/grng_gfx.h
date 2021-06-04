#pragma once

#include "grng_camera.h"
#include "grng_window_def.h"

#include <chrono>

using namespace std::chrono;


class grng_gfx
{
private:
	static int				curr_win_id;
	static float			win_fps[GRNG_MAX_WIN_COUNT];
	static GRNG_CAMERA		*curr_camera;

public:
	static void				set_curr_camera(GRNG_CAMERA *cam)
	{
		grng_gfx::curr_camera = cam;
	}

	static void				set_win(int id)
	{
		grng_gfx::curr_win_id = id;
	}

	static void				set_fps(float fps)
	{
		grng_gfx::win_fps[grng_gfx::curr_win_id] = fps;
	}


	static GRNG_CAMERA		*get_curr_camera()
	{
		return (grng_gfx::curr_camera);
	}

	static float			get_fps()
	{
		return (grng_gfx::win_fps[grng_gfx::curr_win_id]);
	}
};

using GRNG_GFX = grng_gfx;
