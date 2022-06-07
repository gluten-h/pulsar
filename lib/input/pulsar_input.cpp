
#include "pulsar_input.h"


void	pulsar::input::one_frame_reset()
{
	input::one_frame_reset_mouse();
	input::one_frame_reset_keyboard();
}

void	pulsar::input::full_reset()
{
	input::full_reset_mouse();
	input::full_reset_keyboard();
}
