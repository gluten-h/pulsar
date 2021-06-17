#pragma once

#include "grng_math.h"
#include "grng_gfx.h"


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

	public:
		static void			set_delta_event(int x, int y)
		{
			grng_mouse::delta.x = x;
			grng_mouse::delta.y = y;
		}

		static void			set_global_pos_event(int x, int y)
		{
			grng_mouse::global_pos.x = x;
			grng_mouse::global_pos.y = y;
		}

		static void			set_global_pos(int x, int y)
		{
			SetCursorPos(x, y);
			grng_mouse::set_global_pos_event(x, y);
		}


		static void			set_lmb_down_event();
		static void			set_rmb_down_event();
		static void			set_mmb_down_event();
		static void			set_lmb_up_event();
		static void			set_rmb_up_event();
		static void			set_mmb_up_event();


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
			grng_mouse::delta = { 0, 0 };

			grng_mouse::b_lmb_down = false;
			grng_mouse::b_lmb_up = false;
			grng_mouse::b_rmb_down = false;
			grng_mouse::b_rmb_up = false;
			grng_mouse::b_mmb_down = false;
			grng_mouse::b_mmb_up = false;
		}
	};

	using GRNG_MOUSE = grng_mouse;
}
