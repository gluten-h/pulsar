
#include "win_manager.h"


void		PULSAR::WIN_MANAGER::add_win_update_secure(unsigned int win_id, PULSAR::WIN_UPDATE_DEF win_update, void *win_update_data)
{
	PULSAR::WINDOW *win_ptr = PULSAR::WIN_MANAGER::win.get_secure(win_id);
	if (!win_ptr)
		return;
	win_ptr->add_update(win_update, win_update_data);
}

void		PULSAR::WIN_MANAGER::add_win_update(unsigned int win_id, PULSAR::WIN_UPDATE_DEF win_update, void *win_update_data)
{
	PULSAR::WINDOW *win_ptr = PULSAR::WIN_MANAGER::win.get(win_id);
	win_ptr->add_update(win_update, win_update_data);
}

void		PULSAR::WIN_MANAGER::remove_win_update_secure(unsigned int win_id, PULSAR::WIN_UPDATE_DEF win_update)
{
	PULSAR::WINDOW *win_ptr = PULSAR::WIN_MANAGER::win.get_secure(win_id);
	if (!win_ptr)
		return;
	win_ptr->remove_update(win_update);
}

void		PULSAR::WIN_MANAGER::remove_win_update(unsigned int win_id, PULSAR::WIN_UPDATE_DEF win_update)
{
	PULSAR::WINDOW *win_ptr = PULSAR::WIN_MANAGER::win.get(win_id);
	win_ptr->remove_update(win_update);
}
