#pragma once


#include "igrng_d3d.h"
#include "grng_window.h"
#include "grng_window_def.h"
#include "grng_piston.h"
#include "grng_gfx.h"
#include "grng_input.h"

#include <algorithm>
#include <unordered_map>
#include <mutex>


class grng_wm : public IGRNG_D3D
{
private:
	static HINSTANCE			h_instance;
	static WNDCLASSEX			wc;

	static GRNG_PISTON<GRNG_WINDOW, GRNG_MAX_WIN_COUNT>				win;
	static std::unordered_map<HWND, int>							hwnd_map;
	static const GRNG_IPISTON<GRNG_WINDOW, GRNG_MAX_WIN_COUNT>		*iwin;


	static LRESULT CALLBACK	win_proc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
	{
		int win_id = grng_wm::hwnd_map[hwnd];
		GRNG_WINDOW *win_ptr = grng_wm::win.get(win_id);

		switch (msg)
		{
			case WM_CLOSE:
			{
				grng_wm::destroy_win_memory(win_id);
				DestroyWindow(hwnd);
				if (grng_wm::iwin->size <= 0)
				{
					PostQuitMessage(0);
					return (0);
				}
				return (0);
			}
			case WM_LBUTTONDOWN:
			{
				GRNG_INPUT::GRNG_MOUSE::set_lmb_down_event();
				break;
			}
			case WM_LBUTTONUP:
			{
				GRNG_INPUT::GRNG_MOUSE::set_lmb_up_event();
				break;
			}
			case WM_RBUTTONDOWN:
			{
				GRNG_INPUT::GRNG_MOUSE::set_rmb_down_event();
				break;
			}
			case WM_RBUTTONUP:
			{
				GRNG_INPUT::GRNG_MOUSE::set_rmb_up_event();
				break;
			}
			case WM_MBUTTONDOWN:
			{
				GRNG_INPUT::GRNG_MOUSE::set_mmb_down_event();
				break;
			}
			case WM_MBUTTONUP:
			{
				GRNG_INPUT::GRNG_MOUSE::set_mmb_up_event();
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
					GRNG_INPUT::GRNG_MOUSE::set_lmb_up_event();
					GRNG_INPUT::GRNG_MOUSE::set_rmb_up_event();
					GRNG_INPUT::GRNG_MOUSE::set_mmb_up_event();
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
				
					GRNG_INPUT::GRNG_MOUSE::set_delta_event(ri->data.mouse.lLastX, ri->data.mouse.lLastY);
					GRNG_INPUT::GRNG_MOUSE::set_global_pos_event(g_pos.x, g_pos.y);
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


	static void			init_wnd_class(const HINSTANCE h_instance)
	{
		grng_wm::h_instance = h_instance;
		ZeroMemory(&grng_wm::wc, sizeof(WNDCLASSEX));

		grng_wm::wc.cbSize = sizeof(WNDCLASSEX);
		grng_wm::wc.style = CS_OWNDC;
		grng_wm::wc.lpfnWndProc = grng_wm::win_proc;
		grng_wm::wc.cbClsExtra = 0;
		grng_wm::wc.cbWndExtra = 0;
		grng_wm::wc.hInstance = h_instance;
		grng_wm::wc.hIcon = NULL;
		grng_wm::wc.hCursor = NULL;
		grng_wm::wc.hbrBackground = NULL;
		grng_wm::wc.lpszMenuName = NULL;
		grng_wm::wc.lpszClassName = GRNG_WIN_CLASS_NAME;
		grng_wm::wc.hIconSm = NULL;
		grng_wm::wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
		RegisterClassEx(&grng_wm::wc);


		RAWINPUTDEVICE rid;
		rid.usUsagePage = 0x01;
		rid.usUsage = 0x02;
		rid.dwFlags = 0;
		rid.hwndTarget = NULL;
		RegisterRawInputDevices(&rid, 1u, sizeof(RAWINPUTDEVICE));
	}

	static void			init_win()
	{
		grng_wm::iwin = grng_wm::win.get_ipiston();
	}


	static void			destroy_win_memory(int win_id)
	{
		GRNG_WINDOW *win_ptr = grng_wm::win.get(win_id);

		grng_wm::hwnd_map.erase(win_ptr->hwnd);
		win_ptr->destroy();
		grng_wm::win.remove(win_id);
	}

public:
	static void			create(const HINSTANCE h_instance)
	{
		IGRNG_D3D();
		grng_wm::init_wnd_class(h_instance);
		grng_wm::init_win();
	}

	static void			destroy()
	{
		int i = -1;
		while (++i < GRNG_MAX_WIN_COUNT)
		{
			if (grng_wm::win.get_secure(i))
				grng_wm::destroy_win_memory(i);
		}
	}


	static bool			win_event()
	{
		GRNG_INPUT::GRNG_MOUSE::reset_input();

		static MSG msg;

		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				return (false);
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return (true);
	}


	static int			create_window(const LPCWSTR win_name, const DWORD win_style, int x, int y, int w, int h, GRNG_WIN_PROC_DEF win_proc, void *win_proc_data)
	{
		if (grng_wm::iwin->size >= GRNG_MAX_WIN_COUNT)
			return (-1);

		GRNG_WINDOW *win_ptr = grng_wm::win.get(grng_wm::win.next_id());

		win_ptr->create(win_name, win_style, x, y, w, h, win_proc, win_proc_data, grng_wm::h_instance);
		int win_id = grng_wm::win.add(*win_ptr);
		grng_wm::hwnd_map[win_ptr->hwnd] = win_id;
		win_ptr->win_id = win_id;

		return (win_id);
	}

	static void			destroy_win_secure(unsigned int win_id)
	{
		GRNG_WINDOW *win_ptr = grng_wm::win.get_secure(win_id);
		if (!win_ptr)
			return;
	
		grng_wm::destroy_win_memory(win_id);
	}
	static void			destroy_win(unsigned int win_id)
	{
		grng_wm::destroy_win_memory(win_id);
	}


	static const GRNG_IPISTON<GRNG_WINDOW, GRNG_MAX_WIN_COUNT>		*get_iwin()
	{
		return (grng_wm::iwin);
	}


	static void			add_win_update_secure(unsigned int win_id, GRNG_WIN_UPDATE_DEF win_update, void *win_update_data);
	static void			add_win_update(unsigned int win_id, GRNG_WIN_UPDATE_DEF win_update, void *win_update_data);
	static void			remove_win_update_secure(unsigned int win_id, GRNG_WIN_UPDATE_DEF win_update);
	static void			remove_win_update(unsigned int win_id, GRNG_WIN_UPDATE_DEF win_update);


	static void			set_camera_secure(unsigned int win_id, GRNG_CAMERA &cam)
	{
		GRNG_WINDOW *win_ptr = grng_wm::win.get_secure(win_id);
		if (!win_ptr)
			return;
		win_ptr->set_camera(cam);
	}
	static void			set_camera(unsigned int win_id, GRNG_CAMERA &cam)
	{
		GRNG_WINDOW *win_ptr = grng_wm::win.get(win_id);
		win_ptr->set_camera(cam);
	}


	static void			set_scene_secure(unsigned int win_id, GRNG_SCENE &scene)
	{
		GRNG_WINDOW *win_ptr = grng_wm::win.get_secure(win_id);
		if (!win_ptr)
			return;
		win_ptr->set_scene(scene);
	}
	static void			set_scene(unsigned int win_id, GRNG_SCENE &scene)
	{
		GRNG_WINDOW *win_ptr = grng_wm::win.get(win_id);
		win_ptr->set_scene(scene);
	}


	static void			clamp_cursor_secure(unsigned int win_id)
	{
		GRNG_WINDOW *win_ptr = grng_wm::win.get_secure(win_id);
		if (!win_ptr)
			return;
		win_ptr->clamp_cursor();
	}
	static void			clamp_cursor(unsigned int win_id)
	{
		GRNG_WINDOW *win_ptr = grng_wm::win.get(win_id);
		win_ptr->clamp_cursor();
	}

	static void			free_cursor_secure(unsigned int win_id)
	{
		GRNG_WINDOW *win_ptr = grng_wm::win.get_secure(win_id);
		if (!win_ptr)
			return;
		win_ptr->free_cursor();
	}
	static void			free_cursor(unsigned int win_id)
	{
		GRNG_WINDOW *win_ptr = grng_wm::win.get(win_id);
		win_ptr->free_cursor();
	}

	static void			hide_cursor_secure(unsigned int win_id)
	{
		GRNG_WINDOW *win_ptr = grng_wm::win.get_secure(win_id);
		if (!win_ptr)
			return;
		win_ptr->hide_cursor();
	}
	static void			hide_cursor(unsigned int win_id)
	{
		GRNG_WINDOW *win_ptr = grng_wm::win.get(win_id);
		win_ptr->hide_cursor();
	}

	static void			show_cursor_secure(unsigned int win_id)
	{
		GRNG_WINDOW *win_ptr = grng_wm::win.get_secure(win_id);
		if (!win_ptr)
			return;
		win_ptr->show_cursor();
	}
	static void			show_cursor(unsigned int win_id)
	{
		GRNG_WINDOW *win_ptr = grng_wm::win.get(win_id);
		win_ptr->show_cursor();
	}
};


using GRNG_WM = grng_wm;
