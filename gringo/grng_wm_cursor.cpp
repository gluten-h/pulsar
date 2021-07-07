
#include "grng_win_manager.h"


void			grng_wm::clamp_cursor_secure(unsigned int win_id)
{
	GRNG_WINDOW *win_ptr = grng_wm::win.get_secure(win_id);
	if (!win_ptr)
		return;
	win_ptr->clamp_cursor();
}
void			grng_wm::clamp_cursor(unsigned int win_id)
{
	GRNG_WINDOW *win_ptr = grng_wm::win.get(win_id);
	win_ptr->clamp_cursor();
}

void			grng_wm::free_cursor_secure(unsigned int win_id)
{
	GRNG_WINDOW *win_ptr = grng_wm::win.get_secure(win_id);
	if (!win_ptr)
		return;
	win_ptr->free_cursor();
}
void			grng_wm::free_cursor(unsigned int win_id)
{
	GRNG_WINDOW *win_ptr = grng_wm::win.get(win_id);
	win_ptr->free_cursor();
}

void			grng_wm::hide_cursor_secure(unsigned int win_id)
{
	GRNG_WINDOW *win_ptr = grng_wm::win.get_secure(win_id);
	if (!win_ptr)
		return;
	win_ptr->hide_cursor();
}
void			grng_wm::hide_cursor(unsigned int win_id)
{
	GRNG_WINDOW *win_ptr = grng_wm::win.get(win_id);
	win_ptr->hide_cursor();
}

void			grng_wm::show_cursor_secure(unsigned int win_id)
{
	GRNG_WINDOW *win_ptr = grng_wm::win.get_secure(win_id);
	if (!win_ptr)
		return;
	win_ptr->show_cursor();
}
void			grng_wm::show_cursor(unsigned int win_id)
{
	GRNG_WINDOW *win_ptr = grng_wm::win.get(win_id);
	win_ptr->show_cursor();
}
