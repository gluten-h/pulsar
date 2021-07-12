#pragma once

#include "grng_window_def.h"
#include "grng_gfx.h"
#include "grng_deferred_buffer.h"
#include "grng_camera.h"
#include "grng_scene.h"
#include "grng_depth_stencil.h"

#include <unordered_map>
#include <unordered_set>
#include <chrono>

using namespace std::chrono;


class  grng_window : public GRNG_ID3D
{
private:
	friend class grng_wm;

private:
	int								win_id = -1;
	HWND							hwnd = NULL;
	GRNG_WIN_PROC_DEF				win_proc = NULL;
	void							*win_proc_data = NULL;

	bool							is_cursor_clamped = false;

	std::unordered_map<GRNG_WIN_UPDATE_DEF, void*>		win_update;
	//std::unordered_map<GRNG_WIN_UPDATE_DEF, std::unordered_set<void*>>	win_upd;


	IDXGISwapChain					*swap_chain = NULL;
	ID3D11Texture2D					*back_buffer_texture = NULL;
	ID3D11RenderTargetView			*back_buffer = NULL;
	GRNG_DEFERRED_BUFFER			deferred_buffer;

	GRNG_CAMERA						*curr_camera = NULL;
	GRNG_SCENE						*curr_scene = NULL;

	GRNG_DS_STATE					skybox_ds_state;


	void		draw_g_pass();
	void		draw_deferred();
	void		draw_skybox();

public:
	grng_window() : GRNG_ID3D(){ }
	grng_window(const grng_window &win) : GRNG_ID3D()
	{
		this->hwnd = win.hwnd;
		this->win_proc = win.win_proc;
		this->win_proc_data = win.win_proc_data;

		this->swap_chain = win.swap_chain;
		this->back_buffer_texture = win.back_buffer_texture;
		this->back_buffer = win.back_buffer;
		this->deferred_buffer = win.deferred_buffer;

		this->skybox_ds_state = win.skybox_ds_state;
	}

	~grng_window()
	{
		this->destroy();
	}


	void		update();
	void		draw();
	void		present();

	void		create(const LPCWSTR win_name, const DWORD win_style, int x, int y, int w, int h, GRNG_WIN_PROC_DEF win_proc, void *win_proc_data, HINSTANCE h_instance);
	void		destroy();

	void		add_update(GRNG_WIN_UPDATE_DEF win_update, void *win_update_data);
	void		remove_update(GRNG_WIN_UPDATE_DEF win_update);

	void		set_camera(GRNG_CAMERA &cam);
	void		set_scene(GRNG_SCENE &scene);

	void		hide_cursor();
	void		show_cursor();
	void		clamp_cursor();
	void		free_cursor();
};

using GRNG_WINDOW = grng_window;
