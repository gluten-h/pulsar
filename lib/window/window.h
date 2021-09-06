#pragma once

#include "exc_macros.h"
#include "def_window.h"
#include "gfx.h"
#include "deferred_buffer.h"
#include "camera.h"
#include "scene.h"
#include "depth_stencil.h"
#include "render_target.h"

//#include "rg.h"

#include <unordered_map>
#include <unordered_set>
#include <chrono>

using namespace std::chrono;


namespace PULSAR
{
	class  WINDOW : public PULSAR::PULSAR_ID3D
	{
	private:
		friend class WIN_MANAGER;

	private:
		int						win_id = -1;
		HWND					hwnd = NULL;
		PULSAR::WIN_PROC_DEF	win_proc = NULL;
		void					*win_proc_data = NULL;

		bool		is_cursor_clamped = false;

		std::unordered_map<PULSAR::WIN_UPDATE_DEF, void*>		win_update;										//	TODO: FIGURE SOMETHING OUT
		//std::unordered_map<WIN_UPDATE_DEF, std::unordered_set<void*>>	win_upd;


		PULSAR::RENDER_TARGET		render_target;
		PULSAR::DEFERRED_BUFFER		deferred_buffer;

		PULSAR::CAMERA	*curr_camera = NULL;
		PULSAR::SCENE	*curr_scene = NULL;

		PULSAR::DS_STATE	skybox_ds_state;


		//rg		*rg = NULL;


		void	draw_g_pass();
		void	draw_deferred();
		void	draw_skybox();
		void	draw_post_effects();

		void	copy_assign(const WINDOW &win)
		{
			this->hwnd = win.hwnd;
			this->win_proc = win.win_proc;
			this->win_proc_data = win.win_proc_data;

			this->render_target = win.render_target;
			this->deferred_buffer = win.deferred_buffer;

			this->skybox_ds_state = win.skybox_ds_state;
		}

	public:
		WINDOW		&operator=(const WINDOW &win)
		{
			this->copy_assign(win);

			return (*this);
		}
		WINDOW(const WINDOW &win) : PULSAR::PULSAR_ID3D()
		{
			this->copy_assign(win);
		}
		WINDOW() : PULSAR::PULSAR_ID3D(){ }
		~WINDOW()
		{
			this->destroy();
		}


		void	update();
		void	draw();
		void	present();

		void	create(const LPCTSTR win_name, const DWORD win_style, int x, int y, int w, int h, WIN_PROC_DEF win_proc, void *win_proc_data, HINSTANCE h_instance);
		void	destroy();

		void	add_update(WIN_UPDATE_DEF win_update, void *win_update_data);
		void	remove_update(WIN_UPDATE_DEF win_update);

		void	set_camera(CAMERA *cam);
		void	set_scene(SCENE *scene);

		HWND	get_hwnd() const;

		void	hide_cursor();
		void	show_cursor();
		void	clamp_cursor();
		void	free_cursor();
	};
}
