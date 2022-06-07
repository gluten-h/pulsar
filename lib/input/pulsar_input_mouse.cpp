
#include "pulsar_input.h"


XMUINT2		pulsar::input::m_mouse_pos = { 0u, 0u };
XMINT2		pulsar::input::m_mouse_delta = { 0, 0 };
bool		pulsar::input::m_buttons_states[pulsar::input::mouse_button_info::size] = { false };


void	pulsar::input::set_pos(UINT x, UINT y)
{
	input::m_mouse_pos = { x, y };
}

void	pulsar::input::set_delta(int x, int y)
{
	input::m_mouse_delta = { x, y };
}

void	pulsar::input::set_button_down(pulsar::mousecode button)
{
	input::m_buttons_states[button + pressed] = true;
	input::m_buttons_states[button + down] = true;
	input::m_buttons_states[button + up] = false;
}

void	pulsar::input::set_button_up(pulsar::mousecode button)
{
	input::m_buttons_states[button + pressed] = false;
	input::m_buttons_states[button + down] = false;
	input::m_buttons_states[button + up] = true;
}

void	pulsar::input::one_frame_reset_mouse()
{
	input::m_mouse_delta = { 0,0 };

	input::m_buttons_states[lmb + down] = false;
	input::m_buttons_states[lmb + up] = false;
	input::m_buttons_states[rmb + down] = false;
	input::m_buttons_states[rmb + up] = false;
	input::m_buttons_states[mmb + down] = false;
	input::m_buttons_states[mmb + up] = false;
}

void	pulsar::input::full_reset_mouse()
{
	input::m_mouse_delta = { 0,0 };

	input::m_buttons_states[lmb + pressed] = false;
	input::m_buttons_states[lmb + down] = false;
	input::m_buttons_states[lmb + up] = false;
	input::m_buttons_states[rmb + pressed] = false;
	input::m_buttons_states[rmb + down] = false;
	input::m_buttons_states[rmb + up] = false;
	input::m_buttons_states[mmb + pressed] = false;
	input::m_buttons_states[mmb + down] = false;
	input::m_buttons_states[mmb + up] = false;
}

XMUINT2		pulsar::input::get_mouse_position()
{
	return (input::m_mouse_pos);
}

void	pulsar::input::set_mouse_position(UINT x, UINT y)
{
	SetCursorPos(x, y);
}

XMINT2	pulsar::input::mouse_delta()
{
	return (input::m_mouse_delta);
}

bool	pulsar::input::is_buton_pressed(pulsar::mousecode button)
{
	return (input::m_buttons_states[button + pressed]);
}

bool	pulsar::input::is_button_down(pulsar::mousecode button)
{
	return (input::m_buttons_states[button + down]);
}

bool	pulsar::input::is_button_up(pulsar::mousecode button)
{
	return (input::m_buttons_states[button + up]);
}
