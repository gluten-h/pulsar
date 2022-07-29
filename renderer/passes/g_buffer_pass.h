#pragma once

#include "render_graph/pass.h"
#include "config/config.h"
#include "render_graph/sync_input.h"
#include "render_graph/sync_source.h"
#include "render_graph/async_input.h"


namespace pulsar
{
	class depth_stencil_state;
	class vert_shader;
	class geom_shader;
	class input_layout;
	class sampler;
	class depth_stencil_view;
	class render_texture;

	class g_buffer_pass : public pulsar::rg::pass
	{
	private:
		pulsar::depth_stencil_state *mp_dss = NULL;
		pulsar::vert_shader *mp_g_buffer_vs = NULL;
		pulsar::geom_shader *mp_g_buffer_gs = NULL;
		pulsar::input_layout *mp_input_layout = NULL;
		pulsar::sampler *mp_sampler = NULL;

		pulsar::depth_stencil_view *mp_dsv = NULL;
		pulsar::render_texture *mp_g_buffers[pulsar::G_BUFFERS_COUNT] = { NULL };

		pulsar::rg::sync_input<pulsar::depth_stencil_view> *mp_dsv_input = NULL;
		pulsar::rg::sync_source<pulsar::depth_stencil_view> *mp_dsv_source = NULL;

		pulsar::rg::sync_input<pulsar::render_texture> *mp_g_buffers_inputs[pulsar::G_BUFFERS_COUNT] = { NULL };
		pulsar::rg::sync_source<pulsar::render_texture> *mp_g_buffers_sources[pulsar::G_BUFFERS_COUNT] = { NULL };

	public:
		g_buffer_pass &operator=(const g_buffer_pass&) = delete;
		g_buffer_pass &operator=(g_buffer_pass&&) = delete;
		g_buffer_pass(const g_buffer_pass&) = delete;
		g_buffer_pass(g_buffer_pass&&) = delete;
		g_buffer_pass() = delete;
		g_buffer_pass(const std::string &name);
		~g_buffer_pass();

		void	validate() const override;
		void	execute() override;
	};
}
