#pragma once


#include "grng_id3d.h"
#include "grng_window.h"
#include "grng_window_def.h"
#include "grng_piston.h"
#include "grng_gfx.h"
#include "grng_input.h"

#include <algorithm>
#include <unordered_map>
#include <mutex>


class grng_wm : public GRNG_ID3D
{
private:
	static HINSTANCE			h_instance;
	static WNDCLASSEX			wc;

	static GRNG_PISTON<GRNG_WINDOW, GRNG_MAX_WIN_COUNT>				win;
	static std::unordered_map<HWND, int>							hwnd_map;
	static const GRNG_IPISTON<GRNG_WINDOW, GRNG_MAX_WIN_COUNT>		*iwin;


	static LRESULT CALLBACK	win_proc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);

	static void			init_wnd_class(const HINSTANCE h_instance);
	static void			init_win();
	static void			destroy_win_memory(int win_id);

public:
	static void			create(const HINSTANCE h_instance);
	static void			destroy();
	static bool			win_event();


	static int			create_window(const LPCWSTR win_name, const DWORD win_style, int x, int y, int w, int h, GRNG_WIN_PROC_DEF win_proc, void *win_proc_data);
	static void			destroy_win_secure(unsigned int win_id);
	static void			destroy_win(unsigned int win_id);
	static const GRNG_IPISTON<GRNG_WINDOW, GRNG_MAX_WIN_COUNT>		*get_iwin();

	static void			add_win_update_secure(unsigned int win_id, GRNG_WIN_UPDATE_DEF win_update, void *win_update_data);
	static void			add_win_update(unsigned int win_id, GRNG_WIN_UPDATE_DEF win_update, void *win_update_data);
	static void			remove_win_update_secure(unsigned int win_id, GRNG_WIN_UPDATE_DEF win_update);
	static void			remove_win_update(unsigned int win_id, GRNG_WIN_UPDATE_DEF win_update);

	static void			set_camera_secure(unsigned int win_id, GRNG_CAMERA &cam);
	static void			set_camera(unsigned int win_id, GRNG_CAMERA &cam);
	static void			set_scene_secure(unsigned int win_id, GRNG_SCENE &scene);
	static void			set_scene(unsigned int win_id, GRNG_SCENE &scene);

	static void			clamp_cursor_secure(unsigned int win_id);
	static void			clamp_cursor(unsigned int win_id);
	static void			free_cursor_secure(unsigned int win_id);
	static void			free_cursor(unsigned int win_id);
	static void			hide_cursor_secure(unsigned int win_id);
	static void			hide_cursor(unsigned int win_id);
	static void			show_cursor_secure(unsigned int win_id);
	static void			show_cursor(unsigned int win_id);
};


using GRNG_WM = grng_wm;
