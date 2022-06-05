#pragma once

#include "config/config.h"
#include "render_graph/render_graph.h"
#include "render_graph/buffer_source.h"
#include "render_graph/bindable_source.h"


namespace pulsar
{
	class viewport;
	class framebuffer;
	class depth_stencil_view;
	class render_texture;

	class clear_buffers_pass;
	class g_buffer_pass;
	class deferred_pass;
	class skybox_pass;
	class post_effects_pass;
	class present_pass;

	class deferred_render_graph : public pulsar::rg::render_graph
	{
	private:
		pulsar::viewport *mp_viewport = NULL;
		pulsar::framebuffer *mp_framebuffer = NULL;
		pulsar::depth_stencil_view *mp_ds_view = NULL;
		pulsar::render_texture *mp_hdr_buffer = NULL;
		pulsar::render_texture *mp_g_buffers[pulsar::G_BUFFERS_COUNT] = { NULL };

		pulsar::rg::buffer_source<pulsar::framebuffer> *mp_framebuffer_source = NULL;
		pulsar::rg::buffer_source<pulsar::depth_stencil_view> *mp_ds_view_source = NULL;
		pulsar::rg::bindable_source<pulsar::viewport> *mp_viewport_source = NULL;
		pulsar::rg::buffer_source<pulsar::render_texture> *mp_hdr_buffer_source;
		pulsar::rg::buffer_source<pulsar::render_texture> *mp_g_buffers_sources[pulsar::G_BUFFERS_COUNT] = { NULL };


		pulsar::clear_buffers_pass *mp_clear_buffers_pass = NULL;
		pulsar::g_buffer_pass *mp_g_buffer_pass = NULL;
		pulsar::deferred_pass *mp_deferred_pass = NULL;
		pulsar::skybox_pass *mp_skybox_pass = NULL;
		pulsar::post_effects_pass *mp_post_effects_pass = NULL;
		pulsar::present_pass *mp_present_pass = NULL;

	public:
		deferred_render_graph &operator=(const deferred_render_graph&) = delete;
		deferred_render_graph &operator=(deferred_render_graph&&) = delete;
		deferred_render_graph(const deferred_render_graph&) = delete;
		deferred_render_graph(deferred_render_graph&&) = delete;
		deferred_render_graph() = delete;
		deferred_render_graph(pulsar::viewport &viewport, pulsar::framebuffer &framebuffer);
		~deferred_render_graph();
	};
}
