
#include "win_manager.h"


LRESULT CALLBACK		PULSAR::WIN_MANAGER::win_proc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
	int win_id = PULSAR::WIN_MANAGER::hwnd_map[hwnd];
	PULSAR::WINDOW *win_ptr = PULSAR::WIN_MANAGER::win.get(win_id);

	switch (msg)
	{
		case WM_CLOSE:
		{
			PULSAR::WIN_MANAGER::destroy_win_memory(win_id);
			DestroyWindow(hwnd);
			if (PULSAR::WIN_MANAGER::iwin->size <= 0)
			{
				PostQuitMessage(0);
				return (0);
			}
			return (0);
		}
		case WM_LBUTTONDOWN:
		{
			PULSAR::MOUSE::set_lmb_down_event();
			break;
		}
		case WM_LBUTTONUP:
		{
			PULSAR::MOUSE::set_lmb_up_event();
			break;
		}
		case WM_RBUTTONDOWN:
		{
			PULSAR::MOUSE::set_rmb_down_event();
			break;
		}
		case WM_RBUTTONUP:
		{
			PULSAR::MOUSE::set_rmb_up_event();
			break;
		}
		case WM_MBUTTONDOWN:
		{
			PULSAR::MOUSE::set_mmb_down_event();
			break;
		}
		case WM_MBUTTONUP:
		{
			PULSAR::MOUSE::set_mmb_up_event();
			break;
		}
		case WM_ACTIVATE:
		{
			if (w_param & WA_ACTIVE || w_param & WA_CLICKACTIVE)
			{
				if (win_ptr->is_cursor_clamped)
					win_ptr->clamp_cursor();
			}
			else
			{
				PULSAR::MOUSE::set_lmb_up_event();
				PULSAR::MOUSE::set_rmb_up_event();
				PULSAR::MOUSE::set_mmb_up_event();
			}

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

				PULSAR::MOUSE::set_delta_event(ri->data.mouse.lLastX, ri->data.mouse.lLastY);
				PULSAR::MOUSE::set_global_pos_event(g_pos.x, g_pos.y);
			}

			break;
		}
		default:
		break;
	}

	if (win_ptr->win_proc)
		win_ptr->win_proc(msg, w_param, win_ptr->win_proc_data);

	return (DefWindowProc(hwnd, msg, w_param, l_param));
}
