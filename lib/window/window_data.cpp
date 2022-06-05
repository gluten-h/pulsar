
#include "window.h"
#include "exceptions/win_exception.h"
#include "config/config.h"
#include "utils/math.h"


void	pulsar::window::create_window(const LPCSTR name, UINT width, UINT height, BOOL resizable)
{
	RECT wr = { 0, 0, width, height };
	AdjustWindowRect(&wr, pulsar::DEFAULT_WINDOW_SETTINGS.style, FALSE);

	const LPCTSTR class_name = pulsar::DEFAULT_WINDOW_SETTINGS.class_name;
	const DWORD style = pulsar::DEFAULT_WINDOW_SETTINGS.style | (WS_SIZEBOX * resizable);

	HWND hwnd = CreateWindowEx(NULL, class_name, __T(name), style, CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top, NULL, NULL, window::m_h_instance, (LPVOID)this);
	if (!hwnd)
		THROW_LAST_WIN_EXC();

	this->m_viewport.set(width, height);
	this->m_framebuffer.set(hwnd);
	this->m_viewport.link_buffer_resource(&this->m_framebuffer);
}

void	pulsar::window::set_name(const LPCSTR name)
{
	if (!SetWindowText(this->m_hwnd, name))
		THROW_LAST_WIN_EXC();
}

void	pulsar::window::resize(UINT width, UINT height)
{
	RECT wr = { 0, 0, width, height };
	AdjustWindowRect(&wr, GetWindowLongA(this->m_hwnd, GWL_EXSTYLE | GWL_STYLE), FALSE);

	if (!SetWindowPos(this->m_hwnd, NULL, 0, 0, wr.right - wr.left, wr.bottom - wr.top, SWP_NOMOVE | SWP_NOZORDER))
		THROW_LAST_WIN_EXC();

	this->m_viewport.resize(width, height);
}

HWND	pulsar::window::hwnd()
{
	return (this->m_hwnd);
}

pulsar::viewport	&pulsar::window::viewport()
{
	return (this->m_viewport);
}

pulsar::framebuffer		&pulsar::window::framebuffer()
{
	return (this->m_framebuffer);
}

XMUINT2		pulsar::window::size() const
{
	RECT rect;
	if (!GetClientRect(this->m_hwnd, &rect))
		THROW_LAST_WIN_EXC();

	return (XMUINT2(rect.right - rect.left, rect.bottom - rect.top));
}

float	pulsar::window::delta_time() const
{
	return (this->m_delta_time);
}
