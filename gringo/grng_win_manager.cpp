
#include "grng_win_manager.h"


HINSTANCE							grng_wm::h_instance = NULL;
WNDCLASSEX							grng_wm::wc = { 0 };

GRNG_PISTON<GRNG_WINDOW, GRNG_MAX_WIN_COUNT>			grng_wm::win;
std::unordered_map<HWND, int>							grng_wm::hwnd_map;
const GRNG_IPISTON<GRNG_WINDOW, GRNG_MAX_WIN_COUNT>		*grng_wm::iwin;

std::mutex							&grng_wm::mouse_mutex = GRNG_INPUT::GRNG_MOUSE::get_mutex();
