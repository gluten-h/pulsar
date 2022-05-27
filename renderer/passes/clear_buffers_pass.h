#pragma once

#include "render_graph/pass.h"
#include "render_graph/buffer_input.h"
#include "render_graph/buffer_source.h"
#include "config/config.h"


namespace pulsar
{
	class framebuffer;
	class depth_stencil_view;
	class render_texture;

	class clear_buffers_pass : public pulsar::rg::pass
	{
	private:
		pulsar::framebuffer *mp_framebuffer = NULL;
		pulsar::depth_stencil_view *mp_ds_view = NULL;
		pulsar::render_texture *mp_hdr_buffer = NULL;
		pulsar::render_texture *mp_g_buffers[pulsar::G_BUFFERS_COUNT] = { NULL };

		pulsar::rg::buffer_input<pulsar::framebuffer> *mp_framebuffer_input = NULL;
		pulsar::rg::buffer_source<pulsar::framebuffer> *mp_frambuffer_source = NULL;

		pulsar::rg::buffer_input<pulsar::depth_stencil_view> *mp_ds_view_input = NULL;
		pulsar::rg::buffer_source<pulsar::depth_stencil_view> *mp_ds_view_source = NULL;

		pulsar::rg::buffer_input<pulsar::render_texture> *mp_hdr_buffer_input = NULL;
		pulsar::rg::buffer_source<pulsar::render_texture> *mp_hdr_buffer_source = NULL;

		pulsar::rg::buffer_input<pulsar::render_texture> *mp_g_buffers_inputs[pulsar::G_BUFFERS_COUNT] = { NULL };
		pulsar::rg::buffer_source<pulsar::render_texture> *mp_g_buffers_sources[pulsar::G_BUFFERS_COUNT] = { NULL };

	public:
		clear_buffers_pass &operator=(const clear_buffers_pass&) = delete;
		clear_buffers_pass &operator=(clear_buffers_pass&&) = delete;
		clear_buffers_pass(const clear_buffers_pass&) = delete;
		clear_buffers_pass(clear_buffers_pass&&) = delete;
		clear_buffers_pass() = delete;
		clear_buffers_pass(const std::string &name);
		~clear_buffers_pass();

		void	validate() const override;
		void	execute() override;
	};
}
