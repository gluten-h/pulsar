
#include "grng_win_manager.h"


HINSTANCE							grng_wm::h_instance = NULL;
WNDCLASSEX							grng_wm::wc = { 0 };

GRNG_PISTON<GRNG_WINDOW, GRNG_MAX_WIN_COUNT>			grng_wm::win;
std::unordered_map<HWND, int>							grng_wm::hwnd_map;
const GRNG_IPISTON<GRNG_WINDOW, GRNG_MAX_WIN_COUNT>		*grng_wm::iwin;



void			grng_wm::create(const HINSTANCE h_instance)
{
	GRNG_ID3D();
	grng_wm::init_wnd_class(h_instance);
	grng_wm::init_win();
}

void			grng_wm::destroy()
{
	int i = -1;
	while (++i < GRNG_MAX_WIN_COUNT)
	{
		if (grng_wm::win.get_secure(i))
			grng_wm::destroy_win_memory(i);
	}
}

bool			grng_wm::win_event()
{
	GRNG_INPUT::GRNG_MOUSE::reset_input();

	static MSG msg;

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
			return (false);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (true);
}
