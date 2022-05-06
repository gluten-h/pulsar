
#include "window.h"
#include "exceptions/win_exception.h"
#include "def/window.h"
#include "pulsar_input.h"


HINSTANCE	PULSAR::window::m_h_instance = NULL;
WNDCLASSEX	PULSAR::window::m_wc;


PULSAR::window::window()
{
	this->set(PULSAR::DEFAULT_WINDOW_SETTINGS.name, PULSAR::DEFAULT_WINDOW_SETTINGS.style, PULSAR::DEFAULT_WINDOW_SETTINGS.width, PULSAR::DEFAULT_WINDOW_SETTINGS.height);
}

bool	PULSAR::window::process_events()
{
	static MSG msg;

	PULSAR::MOUSE::reset_input();
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
			return (false);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (true);
}

void	PULSAR::window::init(HINSTANCE h_instance)
{
	window::m_h_instance = h_instance;
	ZeroMemory(&window::m_wc, sizeof(WNDCLASSEX));

	window::m_wc.cbSize = sizeof(WNDCLASSEX);
	window::m_wc.style = CS_OWNDC;
	window::m_wc.lpfnWndProc = window::win_proc;
	window::m_wc.cbClsExtra = 0;
	window::m_wc.cbWndExtra = 0;
	window::m_wc.hInstance = h_instance;
	window::m_wc.hIcon = NULL;
	window::m_wc.hCursor = NULL;
	window::m_wc.hbrBackground = NULL;
	window::m_wc.lpszMenuName = NULL;
	window::m_wc.lpszClassName = PULSAR::DEFAULT_WINDOW_SETTINGS.class_name;
	window::m_wc.hIconSm = NULL;
	window::m_wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	if (!RegisterClassEx(&window::m_wc))
		THROW_LAST_WIN_EXC();

	RAWINPUTDEVICE rid;
	rid.usUsagePage = 0x01;
	rid.usUsage = 0x02;
	rid.dwFlags = 0;
	rid.hwndTarget = NULL;
	if (!RegisterRawInputDevices(&rid, 1u, sizeof(RAWINPUTDEVICE)))
		THROW_LAST_WIN_EXC();


	window::get();
}

void	PULSAR::window::present() const
{
	this->m_framebuffer.present();
}
