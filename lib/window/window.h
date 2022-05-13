#pragma once

#include "gfx.h"
#include "_gfx/_gfx.h"
#include "utils/singleton.h"
#include "framebuffer/framebuffer.h"


//#include "deferred_buffer.h"
//#include "camera.h"
//#include "scene.h"
//#include "depth_stencil/depth_stencil_state.h"

//#include "rg.h"

//#include <unordered_map>
//#include <unordered_set>
//#include <chrono>

//using namespace std::chrono;


namespace PULSAR
{
	class window : public PULSAR::singleton<window>
	{
	private:
		static HINSTANCE m_h_instance;

		HWND	m_hwnd = NULL;
		bool	m_cursor_clamped = false;

		PULSAR::framebuffer m_framebuffer;

		//PULSAR::RENDER_TARGET		render_target;
		//PULSAR::DEFERRED_BUFFER		deferred_buffer;

		//PULSAR::CAMERA	*curr_camera = NULL;
		//PULSAR::scene	*curr_scene = NULL;

		//PULSAR::DS_STATE	skybox_ds_state;


		//rg		*rg = NULL;

	private:
		//void	draw_g_pass();
		//void	draw_deferred();
		//void	draw_skybox();
		//void	draw_post_effects();

		void	set(const LPCSTR name, int width, int height);

		static LRESULT CALLBACK		win_proc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);

	public:
		window &operator=(const window&) = delete;
		window &operator=(window&&) = delete;
		window(const window&) = delete;
		window(window&&) = delete;
		window();
		~window() = default;

		static void		init(HINSTANCE h_instance);


		void	set_name(const LPCSTR name);
		void	resize(UINT width, UINT height);

		bool	process_events();
		void	begin_frame();
		//void	update();
		//void	draw();
		void	present() const;

		HWND	hwnd();
		PULSAR::framebuffer		&framebuffer();
		XMUINT2	size() const;

		void	hide_cursor();
		void	show_cursor();
		void	clamp_cursor();
		void	free_cursor();
	};
}
