
#include "grng_mouse.h"


void			GRNG_INPUT::grng_mouse::set_lmb_down_event()
{
	grng_mouse::b_lmb_pressed = true;
	grng_mouse::b_lmb_down = true;
}

void			GRNG_INPUT::grng_mouse::set_rmb_down_event()
{
	grng_mouse::b_rmb_pressed = true;
	grng_mouse::b_rmb_down = true;
}

void			GRNG_INPUT::grng_mouse::set_mmb_down_event()
{
	grng_mouse::b_mmb_pressed = true;
	grng_mouse::b_mmb_down = true;
}

void			GRNG_INPUT::grng_mouse::set_lmb_up_event()
{
	grng_mouse::b_lmb_pressed = false;
	grng_mouse::b_lmb_up = true;
}

void			GRNG_INPUT::grng_mouse::set_rmb_up_event()
{
	grng_mouse::b_rmb_pressed = false;
	grng_mouse::b_rmb_up = true;
}

void			GRNG_INPUT::grng_mouse::set_mmb_up_event()
{
	grng_mouse::b_mmb_pressed = false;
	grng_mouse::b_mmb_up = true;
}
