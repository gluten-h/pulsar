#pragma once

#include "gfx/gfx.h"
#include "config/config.h"
#include "framebuffer/framebuffer.h"
#include <chrono>


namespace pulsar
{
	class window
	{
	private:
		static HINSTANCE m_h_instance;

		HWND	m_hwnd = NULL;
		bool	m_cursor_clamped = false;

		pulsar::framebuffer m_framebuffer;

		std::chrono::time_point<std::chrono::high_resolution_clock> m_begin_frame_time_point;
		float m_frames_time_elapsed = 0.0f;
		uint8_t m_frames_skipped = 0u;
		float m_delta_time = 0.0f;

	private:
		void	set(const LPCSTR name, UINT width, UINT height);

		static LRESULT CALLBACK		win_proc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);

	public:
		window &operator=(const window&) = delete;
		window &operator=(window&&) = delete;
		window(const window&) = delete;
		window(window&&) = delete;
		window() = delete;
		window(const LPCSTR name = pulsar::DEFAULT_WINDOW_SETTINGS.name, UINT width = pulsar::DEFAULT_WINDOW_SETTINGS.width, UINT height = pulsar::DEFAULT_WINDOW_SETTINGS.height);
		~window() = default;

		static void		init(HINSTANCE h_instance);

		void	set_name(const LPCSTR name);
		void	resize(UINT width, UINT height);

		bool	process_events();
		void	begin_frame();
		void	end_frame();

		HWND	hwnd();
		pulsar::framebuffer		&framebuffer();
		XMUINT2	size() const;
		float	delta_time() const;

		void	hide_cursor();
		void	show_cursor();
		void	clamp_cursor();
		void	free_cursor();
	};
}
