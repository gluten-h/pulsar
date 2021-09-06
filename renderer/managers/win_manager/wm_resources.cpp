
#include "win_manager.h"


void		PULSAR::WIN_MANAGER::init_wnd_class(const HINSTANCE h_instance)
{
	PULSAR::WIN_MANAGER::h_instance = h_instance;
	ZeroMemory(&PULSAR::WIN_MANAGER::wc, sizeof(WNDCLASSEX));

	PULSAR::WIN_MANAGER::wc.cbSize = sizeof(WNDCLASSEX);
	PULSAR::WIN_MANAGER::wc.style = CS_OWNDC;
	PULSAR::WIN_MANAGER::wc.lpfnWndProc = PULSAR::WIN_MANAGER::win_proc;
	PULSAR::WIN_MANAGER::wc.cbClsExtra = 0;
	PULSAR::WIN_MANAGER::wc.cbWndExtra = 0;
	PULSAR::WIN_MANAGER::wc.hInstance = h_instance;
	PULSAR::WIN_MANAGER::wc.hIcon = NULL;
	PULSAR::WIN_MANAGER::wc.hCursor = NULL;
	PULSAR::WIN_MANAGER::wc.hbrBackground = NULL;
	PULSAR::WIN_MANAGER::wc.lpszMenuName = NULL;
	PULSAR::WIN_MANAGER::wc.lpszClassName = WIN_CLASS_NAME;
	PULSAR::WIN_MANAGER::wc.hIconSm = NULL;
	PULSAR::WIN_MANAGER::wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	if (!RegisterClassEx(&PULSAR::WIN_MANAGER::wc))
		THROW_WIN_LAST_EXC();


	RAWINPUTDEVICE rid;
	rid.usUsagePage = 0x01;
	rid.usUsage = 0x02;
	rid.dwFlags = 0;
	rid.hwndTarget = NULL;
	if (!RegisterRawInputDevices(&rid, 1u, sizeof(RAWINPUTDEVICE)))
		THROW_WIN_LAST_EXC();
}

void		PULSAR::WIN_MANAGER::init_win()
{
	PULSAR::WIN_MANAGER::iwin = PULSAR::WIN_MANAGER::win.get_ipiston();
}


void		PULSAR::WIN_MANAGER::destroy_win_memory(int win_id)
{
	PULSAR::WINDOW *win_ptr = PULSAR::WIN_MANAGER::win.get(win_id);

	PULSAR::WIN_MANAGER::hwnd_map.erase(win_ptr->hwnd);
	win_ptr->destroy();
	PULSAR::WIN_MANAGER::win.remove(win_id);
}
