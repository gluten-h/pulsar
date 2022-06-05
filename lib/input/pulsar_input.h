#pragma once

#include "pulsar_mousecodes.h"
#include "utils/math.h"
#include <Windows.h>


namespace pulsar
{
	class input
	{
		friend class window;

	private:
		enum mouse_button_info
		{
			lmb = 0,
			rmb = 3,
			mmb = 6,
			size = 9,

			down = 1,
			up = 2
		};

		static XMUINT2 m_mouse_pos;
		static XMINT2 m_mouse_delta;
		static bool m_buttons_states[mouse_button_info::size];

	private:
		static void		set_pos(UINT x, UINT y)
		{
			input::m_mouse_pos = { x, y };
		}

		static void		set_delta(int x, int y)
		{
			input::m_mouse_delta = { x, y };
		}

		static void		set_button_down(pulsar::mouse_code button)
		{
			input::m_buttons_states[button] = true;
			input::m_buttons_states[button + down] = true;
			input::m_buttons_states[button + up] = false;
		}

		static void		set_button_up(pulsar::mouse_code button)
		{
			input::m_buttons_states[button] = false;
			input::m_buttons_states[button + down] = false;
			input::m_buttons_states[button + up] = true;
		}

		static void		reset()
		{
			input::m_mouse_delta = { 0,0 };

			input::m_buttons_states[lmb + down] = false;
			input::m_buttons_states[lmb + up] = false;
			input::m_buttons_states[rmb + down] = false;
			input::m_buttons_states[rmb + up] = false;
			input::m_buttons_states[mmb + down] = false;
			input::m_buttons_states[mmb + up] = false;
		}

	public:
		input &operator=(const input&) = delete;
		input &operator=(input&&) = delete;
		input(const input&) = delete;
		input(input&&) = delete;
		input() = delete;
		~input() = delete;

		static XMUINT2	get_mouse_position()
		{
			return (input::m_mouse_pos);
		}

		static void		set_mouse_position(UINT x, UINT y)
		{
			SetCursorPos(x, y);
		}

		static XMINT2	mouse_delta()
		{
			return (input::m_mouse_delta);
		}

		static bool		is_buton_pressed(pulsar::mouse_code button)
		{
			return (input::m_buttons_states[button]);
		}

		static bool		is_button_down(pulsar::mouse_code button)
		{
			return (input::m_buttons_states[button + 1]);
		}
		
		static bool		is_button_up(pulsar::mouse_code button)
		{
			return (input::m_buttons_states[button + 2]);
		}
	};
}
