#pragma once

#include "passes/render_queue_pass.h"
#include "config/render_graph.h"
#include "render_graph/buffer_input.h"
#include "render_graph/buffer_source.h"
#include "render_graph/bindable_input.h"
#include "render_graph/bindable_source.h"


namespace PULSAR
{
	class depth_stencil_state;
	class depth_stencil_view;
	class viewport;
	class render_texture;

	class g_buffer_pass : public PULSAR::render_queue_pass
	{
	private:
		PULSAR::depth_stencil_state *mp_ds_state = NULL;

		PULSAR::depth_stencil_view *mp_ds_view = NULL;
		PULSAR::viewport *mp_viewport = NULL;
		PULSAR::render_texture *mp_g_buffers[PULSAR::G_BUFFERS_COUNT] = { NULL };

		PULSAR::rg::buffer_input<PULSAR::depth_stencil_view> *mp_ds_view_input = NULL;
		PULSAR::rg::buffer_source<PULSAR::depth_stencil_view> *mp_ds_view_source = NULL;

		PULSAR::rg::bindable_input<PULSAR::viewport> *mp_viewport_input = NULL;
		PULSAR::rg::bindable_source<PULSAR::viewport> *mp_viewport_source = NULL;

		PULSAR::rg::buffer_input<PULSAR::render_texture> *mp_g_buffers_inputs[PULSAR::G_BUFFERS_COUNT] = { NULL };
		PULSAR::rg::buffer_source<PULSAR::render_texture> *mp_g_buffers_sources[PULSAR::G_BUFFERS_COUNT] = { NULL };

	public:
		g_buffer_pass &operator=(const g_buffer_pass&) = delete;
		g_buffer_pass &operator=(g_buffer_pass&&) = delete;
		g_buffer_pass(const g_buffer_pass&) = delete;
		g_buffer_pass(g_buffer_pass&&) = delete;
		g_buffer_pass() = delete;
		g_buffer_pass(const std::string &name);
		~g_buffer_pass();

		void	validate() const override;
		void	execute(float delta_time) override;
	};
}
