#pragma once

#include "config/render_graph.h"
#include "render_graph/render_graph.h"
#include "render_graph/buffer_source.h"
#include "render_graph/bindable_source.h"


namespace PULSAR
{
	class framebuffer;
	class depth_stencil_view;
	class render_texture;
	class viewport;

	class clear_buffers_pass;
	class g_buffer_pass;
	class present_pass;

	class pulsar_render_graph : public PULSAR::rg::render_graph
	{
	private:
		PULSAR::framebuffer *mp_framebuffer = NULL;
		PULSAR::depth_stencil_view *mp_ds_view = NULL;
		PULSAR::viewport *mp_viewport = NULL;
		PULSAR::render_texture *mp_g_buffers[PULSAR::G_BUFFERS_COUNT] = { NULL };

		PULSAR::rg::buffer_source<PULSAR::framebuffer> *mp_framebuffer_source = NULL;
		PULSAR::rg::buffer_source<PULSAR::depth_stencil_view> *mp_ds_view_source = NULL;
		PULSAR::rg::bindable_source<PULSAR::viewport> *mp_viewport_source = NULL;
		PULSAR::rg::buffer_source<PULSAR::render_texture> *mp_g_buffers_sources[PULSAR::G_BUFFERS_COUNT] = { NULL };


		PULSAR::clear_buffers_pass *mp_clear_buffers_pass = NULL;
		PULSAR::g_buffer_pass *mp_g_buffer_pass = NULL;
		PULSAR::present_pass *mp_present_pass = NULL;

	public:
		pulsar_render_graph &operator=(const pulsar_render_graph&) = delete;
		pulsar_render_graph &operator=(pulsar_render_graph&&) = delete;
		pulsar_render_graph(const pulsar_render_graph&) = delete;
		pulsar_render_graph(pulsar_render_graph&&) = delete;
		pulsar_render_graph() = delete;
		pulsar_render_graph(PULSAR::framebuffer &framebuffer);
		~pulsar_render_graph();
	};
}
