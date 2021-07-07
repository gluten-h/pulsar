
#include "grng_win_manager.h"


void			grng_wm::init_wnd_class(const HINSTANCE h_instance)
{
	grng_wm::h_instance = h_instance;
	ZeroMemory(&grng_wm::wc, sizeof(WNDCLASSEX));

	grng_wm::wc.cbSize = sizeof(WNDCLASSEX);
	grng_wm::wc.style = CS_OWNDC;
	grng_wm::wc.lpfnWndProc = grng_wm::win_proc;
	grng_wm::wc.cbClsExtra = 0;
	grng_wm::wc.cbWndExtra = 0;
	grng_wm::wc.hInstance = h_instance;
	grng_wm::wc.hIcon = NULL;
	grng_wm::wc.hCursor = NULL;
	grng_wm::wc.hbrBackground = NULL;
	grng_wm::wc.lpszMenuName = NULL;
	grng_wm::wc.lpszClassName = GRNG_WIN_CLASS_NAME;
	grng_wm::wc.hIconSm = NULL;
	grng_wm::wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	RegisterClassEx(&grng_wm::wc);


	RAWINPUTDEVICE rid;
	rid.usUsagePage = 0x01;
	rid.usUsage = 0x02;
	rid.dwFlags = 0;
	rid.hwndTarget = NULL;
	RegisterRawInputDevices(&rid, 1u, sizeof(RAWINPUTDEVICE));
}

void			grng_wm::init_win()
{
	grng_wm::iwin = grng_wm::win.get_ipiston();
}


void			grng_wm::destroy_win_memory(int win_id)
{
	GRNG_WINDOW *win_ptr = grng_wm::win.get(win_id);

	grng_wm::hwnd_map.erase(win_ptr->hwnd);
	win_ptr->destroy();
	grng_wm::win.remove(win_id);
}
