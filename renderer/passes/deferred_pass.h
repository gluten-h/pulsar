#pragma once

#include "passes/fullscreen_pass.h"
#include "config/config.h"
#include "render_graph/sync_input.h"
#include "render_graph/sync_source.h"
#include "render_graph/async_input.h"
#include "camera/camera.h"
#include "light/light.h"


namespace pulsar
{
	class frag_shader;
	class depth_stencil_view;
	class render_texture;
	class sampler;

	class deferred_pass : public pulsar::fullscreen_pass
	{
	private:
		pulsar::frag_shader *mp_deferred_fs = NULL;
		pulsar::sampler *mp_sampler = NULL;

		pulsar::render_texture *mp_hdr_buffer = NULL;
		pulsar::depth_stencil_view *mp_dsv = NULL;
		pulsar::render_texture *mp_g_buffers[pulsar::G_BUFFERS_COUNT] = { NULL };

		pulsar::rg::sync_input<pulsar::render_texture> *mp_hdr_buffer_input = NULL;
		pulsar::rg::sync_source<pulsar::render_texture> *mp_hdr_buffer_source = NULL;

		pulsar::rg::sync_input<pulsar::depth_stencil_view> *mp_dsv_input = NULL;
		pulsar::rg::sync_source<pulsar::depth_stencil_view> *mp_dsv_source = NULL;

		pulsar::rg::sync_input<pulsar::render_texture> *mp_g_buffers_inputs[pulsar::G_BUFFERS_COUNT] = { NULL };
		pulsar::rg::sync_source<pulsar::render_texture> *mp_g_buffers_sources[pulsar::G_BUFFERS_COUNT] = { NULL };

	public:
		deferred_pass &operator=(const deferred_pass&) = delete;
		deferred_pass &operator=(deferred_pass&&) = delete;
		deferred_pass(const deferred_pass&) = delete;
		deferred_pass(deferred_pass&&) = delete;
		deferred_pass() = delete;
		deferred_pass(const std::string &name);
		~deferred_pass();

		void	validate() const override;
		void	execute() override;
	};
}
