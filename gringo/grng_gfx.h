#pragma once

#include "grng_camera.h"
#include "grng_window_def.h"

#include <chrono>

using namespace std::chrono;


class grng_gfx
{
private:
	static int				curr_win_id;
	static HWND				curr_hwnd;
	
	static float			delta_time;
	static float			fps;
	static time_point<high_resolution_clock>	last_frame_time;

	static GRNG_CAMERA		*curr_camera;

public:
	static void				set_curr_camera_event(GRNG_CAMERA *cam)
	{
		grng_gfx::curr_camera = cam;
	}

	static void				set_curr_win_event(int id, HWND hwnd)
	{
		grng_gfx::curr_win_id = id;
		grng_gfx::curr_hwnd = hwnd;
	}

	static void				set_delta_time()
	{
		grng_gfx::delta_time = duration_cast<duration<double, std::milli>>(high_resolution_clock::now() - grng_gfx::last_frame_time).count();
		grng_gfx::fps = (1.0f / grng_gfx::delta_time) * 1000.0f;
		grng_gfx::delta_time /= 1000.0f;
		grng_gfx::last_frame_time = high_resolution_clock::now();
	}


	static HWND				get_curr_hwnd()
	{
		return (grng_gfx::curr_hwnd);
	}

	static int				get_curr_win_id()
	{
		return (grng_gfx::curr_win_id);
	}

	static GRNG_CAMERA		*get_curr_camera()
	{
		return (grng_gfx::curr_camera);
	}

	static float			get_delta_time()
	{
		return (grng_gfx::delta_time);
	}

	static float			get_fps()
	{
		return (grng_gfx::fps);
	}
};

using GRNG_GFX = grng_gfx;
