#pragma once

#include "pulsar_exc.h"
#include "win_manager.h"
#include "pulsar_resource_manager.h"
#include "pulsar_input.h"
#include "gfx.h"
#include "deferred_buffer.h"
#include "camera.h"
#include "scene.h"
#include "depth_stencil.h"
#include "render_target.h"

#include "rg.h"

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
		static bool		is_initialized;
		static HINSTANCE	h_instance;
		static WNDCLASSEX	wc;
		static std::unordered_map<HWND, WINDOW*>	hwnd_win;

		
		int		id = -1;
		bool	is_alloc = false;

		HWND	hwnd = NULL;
		bool	is_cursor_clamped = false;
		std::unordered_map<PULSAR::WIN_UPDATE_DEF, void*>	win_update;

		PULSAR::RENDER_TARGET		render_target;
		PULSAR::DEFERRED_BUFFER		deferred_buffer;

		PULSAR::CAMERA	*curr_camera = NULL;
		PULSAR::SCENE	*curr_scene = NULL;

		PULSAR::DS_STATE	skybox_ds_state;


		rg		*rg = NULL;


		void	draw_g_pass();
		void	draw_deferred();
		void	draw_skybox();
		void	draw_post_effects();

		void	copy_assign(const WINDOW &win)
		{
			this->id = win.id;
			this->is_alloc = win.is_alloc;

			this->hwnd = win.hwnd;

			this->render_target = win.render_target;
			this->deferred_buffer = win.deferred_buffer;

			this->skybox_ds_state = win.skybox_ds_state;
		}
		void	create_window(const LPCSTR win_name, const DWORD win_style, int x, int y, int w, int h, HINSTANCE h_instance);

		static void		init_win_class(HINSTANCE h_instance)
		{
			WINDOW::h_instance = h_instance;
			ZeroMemory(&WINDOW::wc, sizeof(WNDCLASSEX));

			WINDOW::wc.cbSize = sizeof(WNDCLASSEX);
			WINDOW::wc.style = CS_OWNDC;
			WINDOW::wc.lpfnWndProc = WINDOW::win_proc;
			WINDOW::wc.cbClsExtra = 0;
			WINDOW::wc.cbWndExtra = 0;
			WINDOW::wc.hInstance = h_instance;
			WINDOW::wc.hIcon = NULL;
			WINDOW::wc.hCursor = NULL;
			WINDOW::wc.hbrBackground = NULL;
			WINDOW::wc.lpszMenuName = NULL;
			WINDOW::wc.lpszClassName = WIN_CLASS_NAME;
			WINDOW::wc.hIconSm = NULL;
			WINDOW::wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
			if (!RegisterClassEx(&WINDOW::wc))
				THROW_WIN_LAST_EXC();

			RAWINPUTDEVICE rid;
			rid.usUsagePage = 0x01;
			rid.usUsage = 0x02;
			rid.dwFlags = 0;
			rid.hwndTarget = NULL;
			if (!RegisterRawInputDevices(&rid, 1u, sizeof(RAWINPUTDEVICE)))
				THROW_WIN_LAST_EXC();
		}

		static LRESULT CALLBACK		win_proc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);

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

		int		get_id() const
		{
			return (this->id);
		}

		static void		init(HINSTANCE h_instance)
		{
			WINDOW::init_win_class(h_instance);

			PULSAR::RESOURCE_MANAGER::add_terminate(WINDOW::terminate);
		}
		static void		terminate()
		{

		}

		static bool		process_events()
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

		static WINDOW	*create(const LPCSTR win_name, const DWORD win_style, int x, int y, int width, int height)
		{
			WINDOW *win = new WINDOW;
			win->id = PULSAR::WIN_MANAGER::get_instance().add(win);
			if (win->id == -1)
			{
				delete win;
				return (NULL);
			}
			win->create_window(win_name, win_style, x, y, width, height, WINDOW::h_instance);
			win->is_alloc = true;

			return (win);
		}

		void	destroy()
		{
			if (!this->is_alloc)
				return;
			this->is_alloc = false;

			PULSAR::WIN_MANAGER::get_instance().remove(this);
			delete this;
		}

		void	update();
		void	draw();
		void	present();

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
