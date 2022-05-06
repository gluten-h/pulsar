
#include "window.h"


void	PULSAR::window::hide_cursor()
{
	while (ShowCursor(FALSE) >= 0);
}

void	PULSAR::window::show_cursor()
{
	while (ShowCursor(TRUE) > 0);
}

void	PULSAR::window::clamp_cursor()
{
	RECT rect;
	GetClientRect(this->m_hwnd, &rect);
	MapWindowPoints(this->m_hwnd, NULL, (POINT*)(&rect), 2u);
	ClipCursor(&rect);
	this->m_cursor_clamped = true;
}

void	PULSAR::window::free_cursor()
{
	ClipCursor(NULL);
	this->m_cursor_clamped = false;
}
