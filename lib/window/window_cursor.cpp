
#include "window.h"


void		PULSAR::WINDOW::hide_cursor()
{
	while (ShowCursor(FALSE) >= 0);
}

void		PULSAR::WINDOW::show_cursor()
{
	while (ShowCursor(TRUE) > 0);
}

void		PULSAR::WINDOW::clamp_cursor()
{
	RECT rect;
	GetClientRect(this->hwnd, &rect);
	MapWindowPoints(this->hwnd, NULL, reinterpret_cast<POINT*>(&rect), 2u);
	ClipCursor(&rect);
	this->is_cursor_clamped = true;
}

void		PULSAR::WINDOW::free_cursor()
{
	ClipCursor(NULL);
	this->is_cursor_clamped = false;
}
