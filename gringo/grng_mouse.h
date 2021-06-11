#pragma once

#include "grng_math.h"
#include "grng_gfx.h"

#include <mutex>


const long GRNG_MOUSE_DELTA_UPDATE_RATE_NS = 1000000000.0f / 256.0f;
const long GRNG_MOUSE_DELTA_RESET_RATE_NS = 1000000000.0f / 60.0f;


namespace GRNG_INPUT
{
	class grng_mouse
	{
	private:
		static XMINT2		delta;
		static XMINT2		global_pos;

		static bool			b_lmb_pressed;
		static bool			b_rmb_pressed;
		static bool			b_mmb_pressed;

		static bool			b_lmb_down;
		static bool			b_rmb_down;
		static bool			b_mmb_down;

		static bool			b_lmb_up;
		static bool			b_rmb_up;
		static bool			b_mmb_up;


		static std::mutex	mtx;
		static bool			is_initialized;


		static void			mouse_delta_reset()
		{
			static time_point<high_resolution_clock> start = high_resolution_clock::now();

			while (1)
			{
				float elapsed_ns = duration<float, std::nano>(high_resolution_clock::now() - start).count();
				if (elapsed_ns >= GRNG_MOUSE_DELTA_RESET_RATE_NS)
				{
					grng_mouse::mtx.lock();
					grng_mouse::delta = { 0, 0 };
					grng_mouse::mtx.unlock();
					start = high_resolution_clock::now();
				}
			}
		}

	public:
		static void			set_delta(int x, int y)
		{
			grng_mouse::delta.x = x;
			grng_mouse::delta.y = y;
		}

		static void			set_global_pos(int x, int y)
		{
			grng_mouse::global_pos.x = x;
			grng_mouse::global_pos.y = y;
		}


		static void			set_lmb_down();
		static void			set_rmb_down();
		static void			set_mmb_down();
		static void			set_lmb_up();
		static void			set_rmb_up();
		static void			set_mmb_up();


		static XMINT2		get_delta()
		{
			return (grng_mouse::delta);
		}

		static void			get_delta(int &x, int &y)
		{
			x = grng_mouse::delta.x;
			y = grng_mouse::delta.y;
		}

		static XMINT2		get_global_pos()
		{
			return (grng_mouse::global_pos);
		}

		static void			get_global_pos(int &x, int &y)
		{
			x = grng_mouse::global_pos.x;
			y = grng_mouse::global_pos.y;
		}


		static bool			lmb_pressed()
		{
			return (grng_mouse::b_lmb_pressed && (GetActiveWindow() == GRNG_GFX::get_curr_hwnd()));
		}
		static bool			rmb_pressed()
		{
			return (grng_mouse::b_rmb_pressed && (GetActiveWindow() == GRNG_GFX::get_curr_hwnd()));
		}
		static bool			mmb_pressed()
		{
			return (grng_mouse::mmb_pressed && (GetActiveWindow() == GRNG_GFX::get_curr_hwnd()));
		}

		static bool			lmb_down()
		{
			return (grng_mouse::b_lmb_down && (GetActiveWindow() == GRNG_GFX::get_curr_hwnd()));
		}
		static bool			rmb_down()
		{
			return (grng_mouse::b_rmb_down && (GetActiveWindow() == GRNG_GFX::get_curr_hwnd()));
		}
		static bool			mmb_down()
		{
			return (grng_mouse::b_mmb_down && (GetActiveWindow() == GRNG_GFX::get_curr_hwnd()));
		}

		static bool			lmb_up()
		{
			return (grng_mouse::b_lmb_up && (GetActiveWindow() == GRNG_GFX::get_curr_hwnd()));
		}
		static bool			rmb_up()
		{
			return (grng_mouse::b_rmb_up && (GetActiveWindow() == GRNG_GFX::get_curr_hwnd()));
		}
		static bool			mmb_up()
		{
			return (grng_mouse::b_mmb_up && (GetActiveWindow() == GRNG_GFX::get_curr_hwnd()));
		}


		static void			reset_input()
		{
			grng_mouse::b_lmb_down = false;
			grng_mouse::b_lmb_up = false;
			grng_mouse::b_rmb_down = false;
			grng_mouse::b_rmb_up = false;
			grng_mouse::b_mmb_down = false;
			grng_mouse::b_mmb_up = false;
		}


		static std::mutex	&get_mutex()
		{
			return (grng_mouse::mtx);
		}

		static void			start_thread()
		{
			if (grng_mouse::is_initialized)
				return;

			std::thread mouse_thread(grng_mouse::mouse_delta_reset);
			mouse_thread.detach();

			grng_mouse::is_initialized = true;
		}
	};

	using GRNG_MOUSE = grng_mouse;
}
