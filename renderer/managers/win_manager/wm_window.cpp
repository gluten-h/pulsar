
#include "win_manager.h"


int			PULSAR::WIN_MANAGER::create_window(const LPCTSTR win_name, const DWORD win_style, int x, int y, int w, int h, PULSAR::WIN_PROC_DEF win_proc, void *win_proc_data)
{
	if (PULSAR::WIN_MANAGER::iwin->size >= PULSAR::MAX_WIN_COUNT)
		return (-1);

	PULSAR::WINDOW *win_ptr = PULSAR::WIN_MANAGER::win.get(PULSAR::WIN_MANAGER::win.next_id());

	win_ptr->create(win_name, win_style, x, y, w, h, win_proc, win_proc_data, PULSAR::WIN_MANAGER::h_instance);
	int win_id = PULSAR::WIN_MANAGER::win.add(*win_ptr);
	PULSAR::WIN_MANAGER::hwnd_map[win_ptr->hwnd] = win_id;
	win_ptr->win_id = win_id;

	return (win_id);
}

void		PULSAR::WIN_MANAGER::destroy_win_secure(unsigned int win_id)
{
	PULSAR::WINDOW *win_ptr = PULSAR::WIN_MANAGER::win.get_secure(win_id);
	if (!win_ptr)
		return;

	PULSAR::WIN_MANAGER::destroy_win_memory(win_id);
}

void		PULSAR::WIN_MANAGER::destroy_win(unsigned int win_id)
{
	PULSAR::WIN_MANAGER::destroy_win_memory(win_id);
}

const PULSAR::IPISTON<PULSAR::WINDOW, PULSAR::MAX_WIN_COUNT>	*PULSAR::WIN_MANAGER::get_iwin()
{
	return (PULSAR::WIN_MANAGER::iwin);
}
