
#include "window.h"
#include "input/pulsar_input.h"


LRESULT CALLBACK	pulsar::window::win_proc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
	pulsar::window *win = (pulsar::window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

	switch (msg)
	{
		case WM_NCCREATE:
		{
			LPCREATESTRUCT lpcs = (LPCREATESTRUCT)l_param;
			pulsar::window *self = (pulsar::window*)lpcs->lpCreateParams;
			self->m_hwnd = hwnd;
			self->m_framebuffer.set(self->m_hwnd);

			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)self);

			break;
		}
		case WM_CLOSE:
		{
			DestroyWindow(hwnd);
			return (0);
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return (0);
		}
		case WM_ACTIVATE:
		{
			if (w_param & WA_ACTIVE || w_param & WA_CLICKACTIVE)
			{
				if (win->m_is_cursor_clamped)
					win->clamp_cursor();
			}
			else
				pulsar::input::reset();

			break;
		}
		case WM_SIZE:
		{
			static bool a = 0;

			UINT width = LOWORD(l_param);
			UINT height = HIWORD(l_param);

			//std::string msg = std::to_string(width) + ' ' + std::to_string(height) + '\n';
			//OutputDebugString(msg.c_str());

			// TODO: viewport size must be separated from window size
			// TODO: ideally this code must be placed in some kind of event-system
			if (width && height)
				win->viewport().resize(width, height);

			break;
		}
		case WM_INPUT:
		{
			char raw_buffer[sizeof(RAWINPUT)];
			UINT size = sizeof(RAWINPUT);
			GetRawInputData((HRAWINPUT)l_param, RID_INPUT, raw_buffer, &size, sizeof(RAWINPUTHEADER));

			RAWINPUT *raw_input = (RAWINPUT*)raw_buffer;
			if (raw_input->header.dwType == RIM_TYPEMOUSE)
				window::win_proc_mouse(raw_input->data.mouse);

			break;
		}
	}

	return (DefWindowProc(hwnd, msg, w_param, l_param));
}

void	pulsar::window::win_proc_mouse(RAWMOUSE &raw_mouse)
{
	XMINT2 delta;
	if (raw_mouse.usFlags & MOUSE_MOVE_ABSOLUTE)
	{
		static XMINT2 prev_absolute_coord = { 0, 0 };

		bool is_virtual = (raw_mouse.usFlags & MOUSE_VIRTUAL_DESKTOP) == MOUSE_VIRTUAL_DESKTOP;
		int width = GetSystemMetrics(is_virtual ? SM_CXVIRTUALSCREEN : SM_CXSCREEN);
		int height = GetSystemMetrics(is_virtual ? SM_CYVIRTUALSCREEN : SM_CYSCREEN);

		int absolute_x = int((raw_mouse.lLastX / 65535.0f) * width);
		int absolute_y = int((raw_mouse.lLastY / 65535.0f) * height);

		delta = { prev_absolute_coord.x - absolute_x, prev_absolute_coord.y - absolute_y };
		prev_absolute_coord = { absolute_x, absolute_y };
	}
	else
		delta = { raw_mouse.lLastX, raw_mouse.lLastY };

	POINT mouse_pos;
	GetCursorPos(&mouse_pos);

	pulsar::input::set_pos(mouse_pos.x, mouse_pos.y);
	pulsar::input::set_delta(delta.x, delta.y);

	switch (raw_mouse.usButtonFlags)
	{
		case RI_MOUSE_LEFT_BUTTON_DOWN:
		{
			pulsar::input::set_button_down(pulsar::LMB);
			break;
		}
		case RI_MOUSE_LEFT_BUTTON_UP:
		{
			pulsar::input::set_button_up(pulsar::LMB);
			break;
		}
		case RI_MOUSE_RIGHT_BUTTON_DOWN:
		{
			pulsar::input::set_button_down(pulsar::RMB);
			break;
		}
		case RI_MOUSE_RIGHT_BUTTON_UP:
		{
			pulsar::input::set_button_up(pulsar::RMB);
			break;
		}
		case RI_MOUSE_MIDDLE_BUTTON_DOWN:
		{
			pulsar::input::set_button_down(pulsar::MMB);
			break;
		}
		case RI_MOUSE_MIDDLE_BUTTON_UP:
		{
			pulsar::input::set_button_up(pulsar::MMB);
			break;
		}
	}
}

