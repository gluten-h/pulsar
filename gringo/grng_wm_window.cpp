
#include "grng_win_manager.h"


int				grng_win_manager::create_window(const LPCTSTR win_name, const DWORD win_style, int x, int y, int w, int h, GRNG_WIN_PROC_DEF win_proc, void *win_proc_data)
{
	if (grng_win_manager::iwin->size >= GRNG_MAX_WIN_COUNT)
		return (-1);

	GRNG_WINDOW *win_ptr = grng_win_manager::win.get(grng_win_manager::win.next_id());

	win_ptr->create(win_name, win_style, x, y, w, h, win_proc, win_proc_data, grng_win_manager::h_instance);
	int win_id = grng_win_manager::win.add(*win_ptr);
	grng_win_manager::hwnd_map[win_ptr->hwnd] = win_id;
	win_ptr->win_id = win_id;

	return (win_id);
}

void			grng_win_manager::destroy_win_secure(unsigned int win_id)
{
	GRNG_WINDOW *win_ptr = grng_win_manager::win.get_secure(win_id);
	if (!win_ptr)
		return;

	grng_win_manager::destroy_win_memory(win_id);
}

void			grng_win_manager::destroy_win(unsigned int win_id)
{
	grng_win_manager::destroy_win_memory(win_id);
}

const GRNG_IPISTON<GRNG_WINDOW, GRNG_MAX_WIN_COUNT>		*grng_win_manager::get_iwin()
{
	return (grng_win_manager::iwin);
}
