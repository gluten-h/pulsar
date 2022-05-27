
#include "window.h"
//#include "pulsar_input.h"


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
		case WM_LBUTTONDOWN:
		{
			//pulsar::MOUSE::set_lmb_down_event();
			break;
		}
		case WM_LBUTTONUP:
		{
			//pulsar::MOUSE::set_lmb_up_event();
			break;
		}
		case WM_RBUTTONDOWN:
		{
			//pulsar::MOUSE::set_rmb_down_event();
			break;
		}
		case WM_RBUTTONUP:
		{
			//pulsar::MOUSE::set_rmb_up_event();
			break;
		}
		case WM_MBUTTONDOWN:
		{
			//pulsar::MOUSE::set_mmb_down_event();
			break;
		}
		case WM_MBUTTONUP:
		{
			//pulsar::MOUSE::set_mmb_up_event();
			break;
		}
		case WM_ACTIVATE:
		{
			if (w_param & WA_ACTIVE || w_param & WA_CLICKACTIVE)
			{
				if (win->m_cursor_clamped)
					win->clamp_cursor();
			}
			else
			{
				//pulsar::MOUSE::set_lmb_up_event();
				//pulsar::MOUSE::set_rmb_up_event();
				//pulsar::MOUSE::set_mmb_up_event();
			}
			break;
		}
		case WM_SIZE:
		{
			UINT width = LOWORD(l_param);
			UINT height = HIWORD(l_param);

			if (width && height)
				win->framebuffer().resize(width, height);

			break;
		}
		case WM_INPUT:
		{
			char raw_buffer[sizeof(RAWINPUT)];
			UINT size = sizeof(RAWINPUT);
			GetRawInputData(reinterpret_cast<HRAWINPUT>(l_param), RID_INPUT, raw_buffer, &size, sizeof(RAWINPUTHEADER));
			RAWINPUT *ri = reinterpret_cast<RAWINPUT*>(raw_buffer);
			if (ri->header.dwType == RIM_TYPEMOUSE)
			{
				POINT g_pos;
				GetCursorPos(&g_pos);

				//pulsar::MOUSE::set_delta_event(ri->data.mouse.lLastX, ri->data.mouse.lLastY);
				//pulsar::MOUSE::set_global_pos_event(g_pos.x, g_pos.y);
			}
			break;
		}
	}

	return (DefWindowProc(hwnd, msg, w_param, l_param));
}

