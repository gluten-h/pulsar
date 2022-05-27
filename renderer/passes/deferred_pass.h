#pragma once

#include "passes/fullscreen_pass.h"
#include "config/config.h"
#include "render_graph/buffer_input.h"
#include "render_graph/buffer_source.h"
#include "render_graph/bindable_input.h"
#include "const_buffers/frag_const_buffer.h"
#include "camera/camera.h"
#include "light/light.h"


namespace pulsar
{
	class frag_shader;
	class depth_stencil_view;
	class viewport;
	class render_texture;
	class sampler;

	class deferred_pass : public pulsar::fullscreen_pass
	{
	private:
		pulsar::frag_shader *mp_deferred_fs = NULL;
		pulsar::sampler *mp_sampler = NULL;

		pulsar::render_texture *mp_hdr_buffer = NULL;
		pulsar::depth_stencil_view *mp_ds_view = NULL;
		pulsar::viewport *mp_viewport = NULL;
		pulsar::render_texture *mp_g_buffers[pulsar::G_BUFFERS_COUNT] = { NULL };

		pulsar::rg::buffer_input<pulsar::render_texture> *mp_hdr_buffer_input = NULL;
		pulsar::rg::buffer_source<pulsar::render_texture> *mp_hdr_buffer_source = NULL;

		pulsar::rg::buffer_input<pulsar::depth_stencil_view> *mp_ds_view_input = NULL;
		pulsar::rg::buffer_source<pulsar::depth_stencil_view> *mp_ds_view_source = NULL;

		pulsar::rg::bindable_input<pulsar::viewport> *mp_viewport_input = NULL;

		pulsar::rg::buffer_input<pulsar::render_texture> *mp_g_buffers_inputs[pulsar::G_BUFFERS_COUNT] = { NULL };
		pulsar::rg::buffer_source<pulsar::render_texture> *mp_g_buffers_sources[pulsar::G_BUFFERS_COUNT] = { NULL };

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
