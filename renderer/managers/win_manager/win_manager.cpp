
#include "win_manager.h"


HINSTANCE		PULSAR::WIN_MANAGER::h_instance = NULL;
WNDCLASSEX		PULSAR::WIN_MANAGER::wc = { 0 };

PULSAR::PISTON<PULSAR::WINDOW, PULSAR::MAX_WIN_COUNT>			PULSAR::WIN_MANAGER::win;
std::unordered_map<HWND, int>									PULSAR::WIN_MANAGER::hwnd_map;
const PULSAR::IPISTON<PULSAR::WINDOW, PULSAR::MAX_WIN_COUNT>	*PULSAR::WIN_MANAGER::iwin;


void		PULSAR::WIN_MANAGER::create(const HINSTANCE h_instance)
{
	PULSAR_ID3D();
	PULSAR::WIN_MANAGER::init_wnd_class(h_instance);
	PULSAR::WIN_MANAGER::init_win();

	RESOURCE_MANAGER::add_terminate(PULSAR::WIN_MANAGER::destroy);
}

void		PULSAR::WIN_MANAGER::destroy()
{
	int i = -1;
	while (++i < PULSAR::MAX_WIN_COUNT)
	{
		if (PULSAR::WIN_MANAGER::win.get_secure(i))
			PULSAR::WIN_MANAGER::destroy_win_memory(i);
	}
}

bool		PULSAR::WIN_MANAGER::win_event()
{
	PULSAR::MOUSE::reset_input();

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
