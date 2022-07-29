#pragma once

#include "config/config.h"
#include "gfx_resources/framebuffer.h"
#include <chrono>


namespace pulsar
{
	class window
	{
	private:
		static HINSTANCE m_h_instance;
		static window *mp_active_window;

		HWND m_hwnd = NULL;
		bool m_is_cursor_hidden = false;
		bool m_is_cursor_clamped = false;

		pulsar::framebuffer m_framebuffer;

		std::chrono::time_point<std::chrono::high_resolution_clock> m_begin_frame_time_point;
		int64_t m_frames_time_elapsed = 0.0f;
		uint8_t m_frames_skipped = 0u;
		float m_delta_time = 0.0f;

		void	create_window(const LPCSTR name, UINT width, UINT height, BOOL resizable = FALSE);
		static void	set_active_window(pulsar::window *window);

		static void	win_proc_mouse(RAWMOUSE &raw_mouse);
		static void	win_proc_keyboard(RAWKEYBOARD &raw_keyboard);

		static LRESULT CALLBACK	win_proc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);

	public:
		window &operator=(const window&) = delete;
		window &operator=(window&&) = delete;
		window(const window&) = delete;
		window(window&&) = delete;
		window() = delete;
		window(const LPCSTR name = pulsar::DEFAULT_WINDOW_SETTINGS.name, UINT width = pulsar::DEFAULT_WINDOW_SETTINGS.width, UINT height = pulsar::DEFAULT_WINDOW_SETTINGS.height, BOOL resizable = FALSE);
		~window() = default;

		static void		init(HINSTANCE h_instance);
		static pulsar::window	*active_window();

		void	set_name(const LPCSTR name);
		void	resize(UINT width, UINT height);

		bool	process_events();
		void	begin_frame();
		void	end_frame();

		HWND	hwnd();
		pulsar::framebuffer	&framebuffer();
		XMUINT2	size() const;
		float	delta_time() const;

		void	hide_cursor();
		void	show_cursor();
		void	clamp_cursor();
		void	free_cursor();
	
		bool	is_cursor_hidden() const;
		bool	is_cursor_clamped() const;
	};
}
