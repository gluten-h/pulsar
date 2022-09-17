
#include "pulsar_input.h"


uint16_t	pulsar::input::m_keys_pressed[pulsar::KEYCODES_COUNT] = { 0u };
uint16_t	pulsar::input::m_keys_down[pulsar::KEYCODES_COUNT] = { 0u };
uint16_t	pulsar::input::m_keys_up[pulsar::KEYCODES_COUNT];

uint16_t	pulsar::input::m_keys_reset_queue[pulsar::KEYCODES_COUNT * 2] = { 0u };
uint16_t	pulsar::input::m_curr_reset_id = 0u;


void	pulsar::input::set_key_down(pulsar::keycode key, bool E0_prefix)
{
	uint16_t &key_down = input::m_keys_down[key];
	uint16_t &key_pressed = input::m_keys_pressed[key];

	key_down = key_down | (1 << (8 * E0_prefix));
	key_pressed = key_pressed | (1 << (8 * E0_prefix));

	input::m_keys_reset_queue[input::m_curr_reset_id++] = key + pulsar::KEYCODES_COUNT * E0_prefix;
}

void	pulsar::input::set_key_up(pulsar::keycode key, bool E0_prefix)
{
	uint16_t &key_up = input::m_keys_up[key];
	uint16_t &key_pressed = input::m_keys_pressed[key];

	uint16_t layer0_pressed = (key_pressed & 0x00FF) >> 0;
	uint16_t layer1_pressed = (key_pressed & 0xFF00) >> 8;

	key_up = key_up | (1 << (8 * E0_prefix));
	key_pressed = ((layer0_pressed * E0_prefix) << 0) | ((layer1_pressed * !E0_prefix) << 8);

	input::m_keys_reset_queue[input::m_curr_reset_id++] = key + pulsar::KEYCODES_COUNT * E0_prefix;
}

bool	pulsar::input::extract_key_state(pulsar::keycode key, pulsar::keycode keycode)
{
	uint8_t key_E0_state = (key & 0xFF00) >> 8;
	bool E0_prefix = (keycode & 0xFF00) >> 8;

	return ((key >> (8 * E0_prefix)) - ((key_E0_state << 8) * !E0_prefix));
}

void	pulsar::input::one_frame_reset_keyboard()
{
	int i = -1;
	while (++i < input::m_curr_reset_id)
	{
		uint16_t keycode = input::m_keys_reset_queue[i] % pulsar::KEYCODES_COUNT;
		bool E0_prefix = input::m_keys_reset_queue[i] / pulsar::KEYCODES_COUNT;

		uint16_t &key_down = input::m_keys_down[keycode];
		uint16_t &key_up = input::m_keys_up[keycode];

		uint16_t layer0_down = (key_down & 0x00FF) >> 0;
		uint16_t layer1_down = (key_down & 0xFF00) >> 8;
		uint16_t layer0_up = (key_up & 0x00FF) >> 0;
		uint16_t layer1_up = (key_up & 0xFF00) >> 8;

		key_down = ((layer0_down * E0_prefix) << 0) | ((layer1_down * !E0_prefix) << 8);
		key_up = ((layer0_up * E0_prefix) << 0) | ((layer1_up * !E0_prefix) << 8);
	}

	input::m_curr_reset_id = 0u;
}

void	pulsar::input::full_reset_keyboard()
{
	int i = -1;
	while (++i < input::m_curr_reset_id)
	{
		uint16_t keycode = input::m_keys_reset_queue[i] % pulsar::KEYCODES_COUNT;
		bool E0_prefix = input::m_keys_reset_queue[i] / pulsar::KEYCODES_COUNT;

		uint16_t &key_pressed = input::m_keys_pressed[keycode];
		uint16_t &key_down = input::m_keys_down[keycode];
		uint16_t &key_up = input::m_keys_up[keycode];

		uint16_t layer0_pressed = (key_pressed & 0x00FF) >> 0;
		uint16_t layer1_pressed = (key_pressed & 0xFF00) >> 8;
		uint16_t layer0_down = (key_down & 0x00FF) >> 0;
		uint16_t layer1_down = (key_down & 0xFF00) >> 8;
		uint16_t layer0_up = (key_up & 0x00FF) >> 0;
		uint16_t layer1_up = (key_up & 0xFF00) >> 8;

		key_down = ((layer0_pressed * E0_prefix) << 0) | ((layer1_pressed * !E0_prefix) << 8);
		key_down = ((layer0_down * E0_prefix) << 0) | ((layer1_down * !E0_prefix) << 8);
		key_up = ((layer0_up * E0_prefix) << 0) | ((layer1_up * !E0_prefix) << 8);
	}

	input::m_curr_reset_id = 0u;
}

bool	pulsar::input::is_key_pressed(pulsar::keycode key)
{
	return (input::extract_key_state(input::m_keys_pressed[(key & 0x00FF) >> 0], key));
}

bool	pulsar::input::is_key_down(pulsar::keycode key)
{
	return (input::extract_key_state(input::m_keys_down[(key & 0x00FF) >> 0], key));
}

bool	pulsar::input::is_key_up(pulsar::keycode key)
{
	return (input::extract_key_state(input::m_keys_up[(key & 0x00FF) >> 0], key));
}
