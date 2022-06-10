#pragma once

#include "pulsar_mousecodes.h"
#include "pulsar_keycodes.h"
#include "utils/math.h"
#include <unordered_map>
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

			pressed = 0,
			down = 1,
			up = 2
		};

		/*
			there are 3 states of buttons and keys: 'pressed', 'down' and 'up'
			'down' and 'up' are one-frame states, i.e. these will be active only in one frame after certain button/key interaction
			'pressed' will be active as many frames as button/key is down
		*/

		static XMUINT2 m_mouse_pos;
		static XMINT2 m_mouse_delta;
		static bool m_buttons_states[mouse_button_info::size];

		/*
			keycodes' states are stored in 16bit uint, 8bit for each key
			some keycodes can overlap with each other, in that case such keycode has additional byte (E0/E1)
			for example 0xE021 and 0x0021 are diferrent keys, but they have the same first-byte keycode
			E1-prefix isn't supported
		*/
		static uint16_t m_keys_pressed[pulsar::KEYCODES_COUNT];
		static uint16_t m_keys_down[pulsar::KEYCODES_COUNT];
		static uint16_t m_keys_up[pulsar::KEYCODES_COUNT];
		
		static uint16_t m_keys_reset_queue[pulsar::KEYCODES_COUNT * 2];
		static uint16_t m_curr_reset_id;

		static void		set_pos(UINT x, UINT y);
		static void		set_delta(int x, int y);
		static void		set_button_down(pulsar::mousecode button);
		static void		set_button_up(pulsar::mousecode button);

		static void		set_key_down(pulsar::keycode key, bool E0_prefix);
		static void		set_key_up(pulsar::keycode key, bool E0_prefix);
		static bool		extract_key_state(pulsar::keycode key, pulsar::keycode keycode);

		static void		one_frame_reset_mouse();
		static void		one_frame_reset_keyboard();
		static void		full_reset_mouse();
		static void		full_reset_keyboard();

		static void		one_frame_reset();
		static void		full_reset();

	public:
		input &operator=(const input&) = delete;
		input &operator=(input&&) = delete;
		input(const input&) = delete;
		input(input&&) = delete;
		input() = delete;
		~input() = delete;

		static XMUINT2	get_mouse_position();
		static void		set_mouse_position(UINT x, UINT y);
		static XMINT2	mouse_delta();
		static bool		is_buton_pressed(pulsar::mousecode button);
		static bool		is_button_down(pulsar::mousecode button);
		static bool		is_button_up(pulsar::mousecode button);

		static bool		is_key_pressed(pulsar::keycode key);
		static bool		is_key_down(pulsar::keycode key);
		static bool		is_key_up(pulsar::keycode key);
	};
}
