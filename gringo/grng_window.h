#pragma once

#include "grng_exc_macros.h"
#include "grng_window_def.h"
#include "grng_gfx.h"
#include "grng_deferred_buffer.h"
#include "grng_camera.h"
#include "grng_scene.h"
#include "grng_depth_stencil.h"
#include "grng_render_target.h"

#include <unordered_map>
#include <unordered_set>
#include <chrono>

using namespace std::chrono;


class  grng_window : public GRNG_ID3D
{
private:
	friend class grng_win_manager;

private:
	int								win_id = -1;
	HWND							hwnd = NULL;
	GRNG_WIN_PROC_DEF				win_proc = NULL;
	void							*win_proc_data = NULL;

	bool							is_cursor_clamped = false;

	std::unordered_map<GRNG_WIN_UPDATE_DEF, void*>		win_update;										//	TODO: FIGURE SOMETHING OUT
	//std::unordered_map<GRNG_WIN_UPDATE_DEF, std::unordered_set<void*>>	win_upd;


	GRNG_RENDER_TARGET				render_target;
	GRNG_DEFERRED_BUFFER			deferred_buffer;

	GRNG_CAMERA						*curr_camera = NULL;
	GRNG_SCENE						*curr_scene = NULL;

	GRNG_DS_STATE					skybox_ds_state;


	void		draw_g_pass();
	void		draw_deferred();
	void		draw_skybox();
	void		draw_post_effects();

	void		copy_assign(const grng_window &win)
	{
		this->hwnd = win.hwnd;
		this->win_proc = win.win_proc;
		this->win_proc_data = win.win_proc_data;

		this->render_target = win.render_target;
		this->deferred_buffer = win.deferred_buffer;
		
		this->skybox_ds_state = win.skybox_ds_state;
	}

public:
	grng_window		&operator=(const grng_window &win)
	{
		this->copy_assign(win);

		return (*this);
	}
	grng_window(const grng_window &win) : GRNG_ID3D()
	{
		this->copy_assign(win);
	}
	grng_window() : GRNG_ID3D(){ }

	~grng_window()
	{
		this->destroy();
	}


	void		update();
	void		draw();
	void		present();

	void		create(const LPCTSTR win_name, const DWORD win_style, int x, int y, int w, int h, GRNG_WIN_PROC_DEF win_proc, void *win_proc_data, HINSTANCE h_instance);
	void		destroy();

	void		add_update(GRNG_WIN_UPDATE_DEF win_update, void *win_update_data);
	void		remove_update(GRNG_WIN_UPDATE_DEF win_update);

	void		set_camera(GRNG_CAMERA &cam);
	void		set_scene(GRNG_SCENE &scene);

	HWND		get_hwnd() const;

	void		hide_cursor();
	void		show_cursor();
	void		clamp_cursor();
	void		free_cursor();
};

using GRNG_WINDOW = grng_window;
