#pragma once

#include "render_graph/pass.h"
#include "render_graph/buffer_input.h"
#include "render_graph/buffer_source.h"
#include "config/render_graph.h"


namespace PULSAR
{
	class framebuffer;
	class depth_stencil_view;
	class render_texture;

	class clear_buffers_pass : public PULSAR::rg::pass
	{
	private:
		PULSAR::framebuffer *mp_framebuffer = NULL;
		PULSAR::depth_stencil_view *mp_ds_view = NULL;
		PULSAR::render_texture *mp_g_buffers[PULSAR::G_BUFFERS_COUNT] = { NULL };

		PULSAR::rg::buffer_input<PULSAR::framebuffer> *mp_framebuffer_input = NULL;
		PULSAR::rg::buffer_source<PULSAR::framebuffer> *mp_frambuffer_source = NULL;

		PULSAR::rg::buffer_input<PULSAR::depth_stencil_view> *mp_ds_view_input = NULL;
		PULSAR::rg::buffer_source<PULSAR::depth_stencil_view> *mp_ds_view_source = NULL;

		PULSAR::rg::buffer_input<PULSAR::render_texture> *mp_g_buffers_inputs[PULSAR::G_BUFFERS_COUNT] = { NULL };
		PULSAR::rg::buffer_source<PULSAR::render_texture> *mp_g_buffers_sources[PULSAR::G_BUFFERS_COUNT] = { NULL };

	public:
		clear_buffers_pass &operator=(const clear_buffers_pass&) = delete;
		clear_buffers_pass &operator=(clear_buffers_pass&&) = delete;
		clear_buffers_pass(const clear_buffers_pass&) = delete;
		clear_buffers_pass(clear_buffers_pass&&) = delete;
		clear_buffers_pass() = delete;
		clear_buffers_pass(const std::string &name);
		~clear_buffers_pass();

		void	validate() const override;
		void	execute(float delta_time) override;
	};
}
