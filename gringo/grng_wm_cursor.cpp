
#include "grng_win_manager.h"


void			grng_win_manager::clamp_cursor_secure(unsigned int win_id)
{
	GRNG_WINDOW *win_ptr = grng_win_manager::win.get_secure(win_id);
	if (!win_ptr)
		return;
	win_ptr->clamp_cursor();
}
void			grng_win_manager::clamp_cursor(unsigned int win_id)
{
	GRNG_WINDOW *win_ptr = grng_win_manager::win.get(win_id);
	win_ptr->clamp_cursor();
}

void			grng_win_manager::free_cursor_secure(unsigned int win_id)
{
	GRNG_WINDOW *win_ptr = grng_win_manager::win.get_secure(win_id);
	if (!win_ptr)
		return;
	win_ptr->free_cursor();
}
void			grng_win_manager::free_cursor(unsigned int win_id)
{
	GRNG_WINDOW *win_ptr = grng_win_manager::win.get(win_id);
	win_ptr->free_cursor();
}

void			grng_win_manager::hide_cursor_secure(unsigned int win_id)
{
	GRNG_WINDOW *win_ptr = grng_win_manager::win.get_secure(win_id);
	if (!win_ptr)
		return;
	win_ptr->hide_cursor();
}
void			grng_win_manager::hide_cursor(unsigned int win_id)
{
	GRNG_WINDOW *win_ptr = grng_win_manager::win.get(win_id);
	win_ptr->hide_cursor();
}

void			grng_win_manager::show_cursor_secure(unsigned int win_id)
{
	GRNG_WINDOW *win_ptr = grng_win_manager::win.get_secure(win_id);
	if (!win_ptr)
		return;
	win_ptr->show_cursor();
}
void			grng_win_manager::show_cursor(unsigned int win_id)
{
	GRNG_WINDOW *win_ptr = grng_win_manager::win.get(win_id);
	win_ptr->show_cursor();
}
