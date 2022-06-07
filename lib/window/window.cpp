
#include "window.h"
#include <hidusage.h>
#include "exceptions/win_exception.h"
#include "input/pulsar_input.h"


HINSTANCE	pulsar::window::m_h_instance = NULL;
pulsar::window	*pulsar::window::mp_active_window = NULL;


pulsar::window::window(const LPCSTR name, UINT width, UINT height, BOOL resizable)
{
	this->create_window(name, width, height, resizable);
}

void	pulsar::window::init(HINSTANCE h_instance)
{
	window::m_h_instance = h_instance;

	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = window::win_proc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = h_instance;
	wc.hIcon = NULL;
	wc.hCursor = NULL;
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = pulsar::DEFAULT_WINDOW_SETTINGS.class_name;
	wc.hIconSm = NULL;
	wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	if (!RegisterClassEx(&wc))
		THROW_LAST_WIN_EXC();

	RAWINPUTDEVICE rid[2u];

	// mouse
	rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
	rid[0].usUsage = HID_USAGE_GENERIC_MOUSE;
	rid[0].dwFlags = 0u;
	rid[0].hwndTarget = NULL;

	// keyboard
	rid[1].usUsagePage = HID_USAGE_PAGE_GENERIC;
	rid[1].usUsage = HID_USAGE_GENERIC_KEYBOARD;
	rid[1].dwFlags = 0u;
	rid[1].hwndTarget = NULL;

	if (!RegisterRawInputDevices(rid, 2u, sizeof(RAWINPUTDEVICE)))
		THROW_LAST_WIN_EXC();
}

void	pulsar::window::set_active_window(pulsar::window *window)
{
	window::mp_active_window = window;
}

pulsar::window	*pulsar::window::active_window()
{
	return (window::mp_active_window);
}

bool	pulsar::window::process_events()
{
	MSG msg;

	pulsar::input::one_frame_reset();
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
			return (false);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (true);
}

void	pulsar::window::begin_frame()
{
	this->set_active_window(this);

	this->m_begin_frame_time_point = std::chrono::high_resolution_clock::now();
}

void	pulsar::window::end_frame()
{
	this->set_active_window(NULL);

	auto end_frame_time_point = std::chrono::high_resolution_clock::now();
	this->m_frames_time_elapsed += std::chrono::duration_cast<std::chrono::milliseconds>(end_frame_time_point - this->m_begin_frame_time_point).count();
	this->m_frames_skipped++;
	if (this->m_frames_skipped >= FPS_FRAMES_SKIP_COUNT)
	{
		this->m_delta_time = (float)this->m_frames_time_elapsed / (float)this->m_frames_skipped / 1000.0f;
		this->m_frames_time_elapsed = 0.0f;
		this->m_frames_skipped = 0u;
	}
}

void	pulsar::window::hide_cursor()
{
	while (ShowCursor(FALSE) >= 0);
	this->m_is_cursor_hidden = true;
}

void	pulsar::window::show_cursor()
{
	while (ShowCursor(TRUE) > 0);
	this->m_is_cursor_hidden = false;
}

void	pulsar::window::clamp_cursor()
{
	RECT rect;
	GetClientRect(this->m_hwnd, &rect);
	MapWindowPoints(this->m_hwnd, NULL, (POINT*)(&rect), 2u);
	ClipCursor(&rect);
	this->m_is_cursor_clamped = true;
}

void	pulsar::window::free_cursor()
{
	ClipCursor(NULL);
	this->m_is_cursor_clamped = false;
}

bool	pulsar::window::is_cursor_hidden() const
{
	return (this->m_is_cursor_hidden);
}

bool	pulsar::window::is_cursor_clamped() const
{
	return (this->m_is_cursor_clamped);
}
