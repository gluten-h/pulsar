#pragma once

#include "unclassified.h"
#include "camera.h"
#include "def_window.h"

#include <chrono>

using namespace std::chrono;


namespace PULSAR
{
	class WINDOW;

	class GFX : public PULSAR::unclassified
	{
	private:
		static PULSAR::WINDOW	*curr_win;
		static HWND		curr_hwnd;

		static float	delta_time;
		static float	fps;
		static time_point<high_resolution_clock>	last_frame_time;

		static PULSAR::CAMERA	*curr_camera;

	public:
		static void		set_curr_camera_event(PULSAR::CAMERA *cam)
		{
			GFX::curr_camera = cam;
		}

		static void		set_curr_win_event(PULSAR::WINDOW *win, HWND hwnd)
		{
			GFX::curr_win = win;
			GFX::curr_hwnd = hwnd;
		}

		static void		set_delta_time()
		{
			GFX::delta_time = duration_cast<duration<double, std::milli>>(high_resolution_clock::now() - GFX::last_frame_time).count();
			GFX::fps = (1.0f / GFX::delta_time) * 1000.0f;
			GFX::delta_time /= 1000.0f;
			GFX::last_frame_time = high_resolution_clock::now();
		}


		static PULSAR::WINDOW	*get_curr_win()
		{
			return (GFX::curr_win);
		}
		static HWND		get_curr_hwnd()
		{
			return (GFX::curr_hwnd);
		}

		static PULSAR::CAMERA	*get_curr_camera()
		{
			return (GFX::curr_camera);
		}

		static float	get_delta_time()
		{
			return (GFX::delta_time);
		}
		static float	get_fps()
		{
			return (GFX::fps);
		}


		static void		draw_indexed(UINT index_count)
		{
			PULSAR::unclassified::m_id3d.device_context()->DrawIndexed(index_count, 0u, 0u);
			//PULSAR::id3d::device_context()->DrawIndexed(index_count, 0u, 0u);
		}
	};
}
