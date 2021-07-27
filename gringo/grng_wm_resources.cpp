
#include "grng_win_manager.h"


void			grng_win_manager::init_wnd_class(const HINSTANCE h_instance)
{
	grng_win_manager::h_instance = h_instance;
	ZeroMemory(&grng_win_manager::wc, sizeof(WNDCLASSEX));

	grng_win_manager::wc.cbSize = sizeof(WNDCLASSEX);
	grng_win_manager::wc.style = CS_OWNDC;
	grng_win_manager::wc.lpfnWndProc = grng_win_manager::win_proc;
	grng_win_manager::wc.cbClsExtra = 0;
	grng_win_manager::wc.cbWndExtra = 0;
	grng_win_manager::wc.hInstance = h_instance;
	grng_win_manager::wc.hIcon = NULL;
	grng_win_manager::wc.hCursor = NULL;
	grng_win_manager::wc.hbrBackground = NULL;
	grng_win_manager::wc.lpszMenuName = NULL;
	grng_win_manager::wc.lpszClassName = GRNG_WIN_CLASS_NAME;
	grng_win_manager::wc.hIconSm = NULL;
	grng_win_manager::wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	if (!RegisterClassEx(&grng_win_manager::wc))
		GRNG_THROW_WIN_LAST_EXC();


	RAWINPUTDEVICE rid;
	rid.usUsagePage = 0x01;
	rid.usUsage = 0x02;
	rid.dwFlags = 0;
	rid.hwndTarget = NULL;
	if (!RegisterRawInputDevices(&rid, 1u, sizeof(RAWINPUTDEVICE)))
		GRNG_THROW_WIN_LAST_EXC();
}

void			grng_win_manager::init_win()
{
	grng_win_manager::iwin = grng_win_manager::win.get_ipiston();
}


void			grng_win_manager::destroy_win_memory(int win_id)
{
	GRNG_WINDOW *win_ptr = grng_win_manager::win.get(win_id);

	grng_win_manager::hwnd_map.erase(win_ptr->hwnd);
	win_ptr->destroy();
	grng_win_manager::win.remove(win_id);
}
