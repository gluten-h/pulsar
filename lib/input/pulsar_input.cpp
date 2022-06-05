
#include "pulsar_input.h"


XMUINT2		pulsar::input::m_mouse_pos = { 0u, 0u };
XMINT2		pulsar::input::m_mouse_delta = { 0, 0 };
bool		pulsar::input::m_buttons_states[pulsar::input::mouse_button_info::size] = { false };
