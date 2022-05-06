
#include "window.h"
#include "exceptions/win_exception.h"
#include "def/window.h"


void	PULSAR::window::set(const LPCSTR name, int width, int height)
{
	RECT wr = { 0, 0, width, height };
	AdjustWindowRect(&wr, PULSAR::DEFAULT_WINDOW_SETTINGS.style, FALSE);

	const LPCTSTR class_name = PULSAR::DEFAULT_WINDOW_SETTINGS.class_name;
	const DWORD style = PULSAR::DEFAULT_WINDOW_SETTINGS.style;

	HWND hwnd = CreateWindowEx(NULL, class_name, __T(name), style, CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top, NULL, NULL, window::m_h_instance, NULL);
	if (!hwnd)
		THROW_LAST_WIN_EXC();

	this->m_hwnd = hwnd;

	//this->render_target.set(this->m_hwnd, TRUE);
	//this->deferred_buffer.set_deferred_buffer((float)width, (float)height);
	//this->skybox_ds_state.set(TRUE, D3D11_COMPARISON_LESS_EQUAL, D3D11_DEPTH_WRITE_MASK_ZERO);


	//this->rg = rg::create(&this->render_target, &this->deferred_buffer.get_ds_view());
}

void	PULSAR::window::set_name(const LPCSTR name)
{
	if (!SetWindowText(this->m_hwnd, name))
		THROW_LAST_WIN_EXC();
}

void	PULSAR::window::resize(UINT width, UINT height)
{
	RECT wr = { 0, 0, width, height };
	AdjustWindowRect(&wr, GetWindowLongA(this->m_hwnd, GWL_EXSTYLE | GWL_STYLE), FALSE);

	if (!SetWindowPos(this->m_hwnd, NULL, 0, 0, wr.right - wr.left, wr.bottom - wr.top, SWP_NOMOVE | SWP_NOZORDER))
		THROW_LAST_WIN_EXC();

	this->m_framebuffer.resize(width, height);
}

HWND	PULSAR::window::get_hwnd()
{
	return (this->m_hwnd);
}

PULSAR::framebuffer		&PULSAR::window::get_framebuffer()
{
	return (this->m_framebuffer);
}
