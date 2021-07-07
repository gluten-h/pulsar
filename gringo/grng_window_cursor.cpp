
#include "grng_window.h"


void		grng_window::hide_cursor()
{
	while (ShowCursor(FALSE) >= 0);
}

void		grng_window::show_cursor()
{
	while (ShowCursor(TRUE) > 0);
}

void		grng_window::clamp_cursor()
{
	RECT rect;
	GetClientRect(this->hwnd, &rect);
	MapWindowPoints(this->hwnd, NULL, reinterpret_cast<POINT*>(&rect), 2u);
	ClipCursor(&rect);
	this->is_cursor_clamped = true;
}

void		grng_window::free_cursor()
{
	ClipCursor(NULL);
	this->is_cursor_clamped = false;
}
