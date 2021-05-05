
#include "grng_win_manager.h"


HINSTANCE				grng_wm::h_instance = NULL;
WNDCLASSEX				grng_wm::wc = { 0 };
MSG						grng_wm::msg;

IDXGIFactory			*grng_wm::idxgi_factory = NULL;
ID3D11Device			*grng_wm::device = NULL;
ID3D11DeviceContext		*grng_wm::device_context = NULL;

GRNG_PISTON<GRNG_WIN, GRNG_MAX_WIN_COUNT>			grng_wm::win;
std::unordered_map<HWND, int>						grng_wm::hwnd_map;
const GRNG_IPISTON<GRNG_WIN, GRNG_MAX_WIN_COUNT>	*grng_wm::iwin;
