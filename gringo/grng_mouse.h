#pragma once

#include "grng_math.h"


namespace GRNG_INPUT
{
	class grng_mouse
	{
	private:
		static XMINT2		delta;
		static XMINT2		global_pos;

		static bool			lmb_pressed;
		static bool			rmb_pressed;
		static bool			mmb_pressed;

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

		static void			set_lmb(bool lmb_pressed)
		{
			grng_mouse::lmb_pressed = lmb_pressed;
		}

		static void			set_rmb(bool rmb_pressed)
		{
			grng_mouse::rmb_pressed = rmb_pressed;
		}

		static void			set_mmb(bool mmb_pressed)
		{
			grng_mouse::mmb_pressed = mmb_pressed;
		}


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


		static bool			is_lmb_pressed()
		{
			return (grng_mouse::lmb_pressed);
		}

		static bool			is_rmb_pressed()
		{
			return (grng_mouse::rmb_pressed);
		}

		static bool			is_mmb_pressed()
		{
			return (grng_mouse::mmb_pressed);
		}
	};

	using GRNG_MOUSE = grng_mouse;
}
