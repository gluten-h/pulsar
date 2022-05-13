
#include "window.h"
#include "exceptions/win_exception.h"
#include "config/window.h"
#include "pulsar_input.h"
#include "scene/scene.h"
#include "node/node.h"
#include "transform/transform_component.h"
#include "camera/camera_component.h"


HINSTANCE	PULSAR::window::m_h_instance = NULL;


PULSAR::window::window()
{
	this->set(PULSAR::DEFAULT_WINDOW_SETTINGS.name, PULSAR::DEFAULT_WINDOW_SETTINGS.width, PULSAR::DEFAULT_WINDOW_SETTINGS.height);
}

void	PULSAR::window::init(HINSTANCE h_instance)
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
	wc.lpszClassName = PULSAR::DEFAULT_WINDOW_SETTINGS.class_name;
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

	//default window initialization
	window::get();
}

bool	PULSAR::window::process_events()
{
	MSG msg;

	//PULSAR::MOUSE::reset_input();
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
			return (false);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (true);
}

void	PULSAR::window::present() const
{
	this->m_framebuffer.present();
}
