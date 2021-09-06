#pragma once

#include "camera.h"
#include "def_window.h"

#include <chrono>

using namespace std::chrono;


namespace PULSAR
{
	class GFX
	{
	private:
		static int		curr_win_id;
		static HWND		curr_hwnd;

		static float	delta_time;
		static float	fps;
		static time_point<high_resolution_clock>	last_frame_time;

		static PULSAR::CAMERA	*curr_camera;

	public:
		static void		set_curr_camera_event(PULSAR::CAMERA *cam)
		{
			PULSAR::GFX::curr_camera = cam;
		}

		static void		set_curr_win_event(int id, HWND hwnd)
		{
			PULSAR::GFX::curr_win_id = id;
			PULSAR::GFX::curr_hwnd = hwnd;
		}

		static void		set_delta_time()
		{
			PULSAR::GFX::delta_time = duration_cast<duration<double, std::milli>>(high_resolution_clock::now() - PULSAR::GFX::last_frame_time).count();
			PULSAR::GFX::fps = (1.0f / PULSAR::GFX::delta_time) * 1000.0f;
			PULSAR::GFX::delta_time /= 1000.0f;
			PULSAR::GFX::last_frame_time = high_resolution_clock::now();
		}


		static HWND		get_curr_hwnd()
		{
			return (PULSAR::GFX::curr_hwnd);
		}

		static int		get_curr_win_id()
		{
			return (PULSAR::GFX::curr_win_id);
		}

		static PULSAR::CAMERA		*get_curr_camera()
		{
			return (PULSAR::GFX::curr_camera);
		}

		static float	get_delta_time()
		{
			return (PULSAR::GFX::delta_time);
		}

		static float	get_fps()
		{
			return (PULSAR::GFX::fps);
		}
	};
}
