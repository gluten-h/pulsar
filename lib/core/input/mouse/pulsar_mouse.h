#pragma once

#include "math.h"
#include "gfx.h"


namespace PULSAR
{
	class MOUSE
	{
	private:
		static XMINT2	delta;
		static XMINT2	global_pos;

		static bool		b_lmb_pressed;
		static bool		b_rmb_pressed;
		static bool		b_mmb_pressed;

		static bool		b_lmb_down;
		static bool		b_rmb_down;
		static bool		b_mmb_down;

		static bool		b_lmb_up;
		static bool		b_rmb_up;
		static bool		b_mmb_up;

	public:
		static void		set_delta_event(int x, int y)
		{
			MOUSE::delta.x = x;
			MOUSE::delta.y = y;
		}

		static void		set_global_pos_event(int x, int y)
		{
			MOUSE::global_pos.x = x;
			MOUSE::global_pos.y = y;
		}

		static void		set_global_pos(int x, int y)
		{
			SetCursorPos(x, y);
			MOUSE::set_global_pos_event(x, y);
		}


		static void		set_lmb_down_event();
		static void		set_rmb_down_event();
		static void		set_mmb_down_event();
		static void		set_lmb_up_event();
		static void		set_rmb_up_event();
		static void		set_mmb_up_event();


		static XMINT2	get_delta()
		{
			return (MOUSE::delta);
		}

		static void		get_delta(int &x, int &y)
		{
			x = MOUSE::delta.x;
			y = MOUSE::delta.y;
		}

		static XMINT2	get_global_pos()
		{
			return (MOUSE::global_pos);
		}

		static void		get_global_pos(int &x, int &y)
		{
			x = MOUSE::global_pos.x;
			y = MOUSE::global_pos.y;
		}


		static bool		lmb_pressed()
		{
			return (MOUSE::b_lmb_pressed && (GetActiveWindow() == GFX::get_curr_hwnd()));
		}
		static bool		rmb_pressed()
		{
			return (MOUSE::b_rmb_pressed && (GetActiveWindow() == GFX::get_curr_hwnd()));
		}
		static bool		mmb_pressed()
		{
			return (MOUSE::mmb_pressed && (GetActiveWindow() == GFX::get_curr_hwnd()));
		}

		static bool		lmb_down()
		{
			return (MOUSE::b_lmb_down && (GetActiveWindow() == GFX::get_curr_hwnd()));
		}
		static bool		rmb_down()
		{
			return (MOUSE::b_rmb_down && (GetActiveWindow() == GFX::get_curr_hwnd()));
		}
		static bool		mmb_down()
		{
			return (MOUSE::b_mmb_down && (GetActiveWindow() == GFX::get_curr_hwnd()));
		}

		static bool		lmb_up()
		{
			return (MOUSE::b_lmb_up && (GetActiveWindow() == GFX::get_curr_hwnd()));
		}
		static bool		rmb_up()
		{
			return (MOUSE::b_rmb_up && (GetActiveWindow() == GFX::get_curr_hwnd()));
		}
		static bool		mmb_up()
		{
			return (MOUSE::b_mmb_up && (GetActiveWindow() == GFX::get_curr_hwnd()));
		}


		static void		reset_input()
		{
			MOUSE::delta = { 0, 0 };

			MOUSE::b_lmb_down = false;
			MOUSE::b_lmb_up = false;
			MOUSE::b_rmb_down = false;
			MOUSE::b_rmb_up = false;
			MOUSE::b_mmb_down = false;
			MOUSE::b_mmb_up = false;
		}
	};
}
