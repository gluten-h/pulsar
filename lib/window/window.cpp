
#include "window.h"
#include "exceptions/win_exception.h"
//#include "pulsar_input.h"


HINSTANCE	pulsar::window::m_h_instance = NULL;


pulsar::window::window(const LPCSTR name, UINT width, UINT height)
{
	this->set(name, width, height);
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

	RAWINPUTDEVICE rid;
	rid.usUsagePage = 0x01;
	rid.usUsage = 0x02;
	rid.dwFlags = 0;
	rid.hwndTarget = NULL;
	if (!RegisterRawInputDevices(&rid, 1u, sizeof(RAWINPUTDEVICE)))
		THROW_LAST_WIN_EXC();
}

bool	pulsar::window::process_events()
{
	MSG msg;

	//pulsar::MOUSE::reset_input();
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
	this->m_begin_frame_time_point = std::chrono::high_resolution_clock::now();
}

void	pulsar::window::end_frame()
{
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
}

void	pulsar::window::show_cursor()
{
	while (ShowCursor(TRUE) > 0);
}

void	pulsar::window::clamp_cursor()
{
	RECT rect;
	GetClientRect(this->m_hwnd, &rect);
	MapWindowPoints(this->m_hwnd, NULL, (POINT*)(&rect), 2u);
	ClipCursor(&rect);
	this->m_cursor_clamped = true;
}

void	pulsar::window::free_cursor()
{
	ClipCursor(NULL);
	this->m_cursor_clamped = false;
}
