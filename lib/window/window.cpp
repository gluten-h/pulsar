
#include "window.h"


bool	PULSAR::WINDOW::is_initialized = false;

HINSTANCE		PULSAR::WINDOW::h_instance = NULL;
WNDCLASSEX		PULSAR::WINDOW::wc;

std::unordered_map<HWND, PULSAR::WINDOW*>		PULSAR::WINDOW::hwnd_win;


void		PULSAR::WINDOW::create_window(const LPCSTR win_name, const DWORD win_style, int x, int y, int w, int h, HINSTANCE h_instance)
{
	HRESULT hr;

	RECT wr = { 0, 0, w, h };
	AdjustWindowRect(&wr, win_style, FALSE);

	HWND hwnd = CreateWindowEx(NULL, WIN_CLASS_NAME, __T(win_name), win_style, x, y, wr.right - wr.left, wr.bottom - wr.top, NULL, NULL, h_instance, NULL);
	if (!hwnd)
		THROW_WIN_LAST_EXC();

	this->hwnd = hwnd;
	WINDOW::hwnd_win[hwnd] = this;

	this->render_target.set(this->hwnd, TRUE);
	this->deferred_buffer.set_deferred_buffer((float)w, (float)h);
	this->skybox_ds_state.set(TRUE, D3D11_COMPARISON_LESS_EQUAL, D3D11_DEPTH_WRITE_MASK_ZERO);


	this->rg = rg::create(&this->render_target, &this->deferred_buffer.get_ds_view());
}
