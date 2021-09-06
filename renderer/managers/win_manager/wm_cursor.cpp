
#include "win_manager.h"


void		PULSAR::WIN_MANAGER::clamp_cursor_secure(unsigned int win_id)
{
	PULSAR::WINDOW *win_ptr = PULSAR::WIN_MANAGER::win.get_secure(win_id);
	if (!win_ptr)
		return;
	win_ptr->clamp_cursor();
}
void		PULSAR::WIN_MANAGER::clamp_cursor(unsigned int win_id)
{
	PULSAR::WINDOW *win_ptr = PULSAR::WIN_MANAGER::win.get(win_id);
	win_ptr->clamp_cursor();
}

void		PULSAR::WIN_MANAGER::free_cursor_secure(unsigned int win_id)
{
	PULSAR::WINDOW *win_ptr = PULSAR::WIN_MANAGER::win.get_secure(win_id);
	if (!win_ptr)
		return;
	win_ptr->free_cursor();
}
void		PULSAR::WIN_MANAGER::free_cursor(unsigned int win_id)
{
	PULSAR::WINDOW *win_ptr = PULSAR::WIN_MANAGER::win.get(win_id);
	win_ptr->free_cursor();
}

void		PULSAR::WIN_MANAGER::hide_cursor_secure(unsigned int win_id)
{
	PULSAR::WINDOW *win_ptr = PULSAR::WIN_MANAGER::win.get_secure(win_id);
	if (!win_ptr)
		return;
	win_ptr->hide_cursor();
}
void		PULSAR::WIN_MANAGER::hide_cursor(unsigned int win_id)
{
	PULSAR::WINDOW *win_ptr = PULSAR::WIN_MANAGER::win.get(win_id);
	win_ptr->hide_cursor();
}

void		PULSAR::WIN_MANAGER::show_cursor_secure(unsigned int win_id)
{
	PULSAR::WINDOW *win_ptr = PULSAR::WIN_MANAGER::win.get_secure(win_id);
	if (!win_ptr)
		return;
	win_ptr->show_cursor();
}
void		PULSAR::WIN_MANAGER::show_cursor(unsigned int win_id)
{
	PULSAR::WINDOW *win_ptr = PULSAR::WIN_MANAGER::win.get(win_id);
	win_ptr->show_cursor();
}
