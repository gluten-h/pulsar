#pragma once

#include "render_graph/pass.h"
#include "render_graph/buffer_input.h"
#include "render_graph/buffer_source.h"
#include "render_graph/bindable_input.h"


namespace pulsar
{
	class vert_shader;
	class frag_shader;
	class depth_stencil_state;
	class sampler;
	class input_layout;
	class render_texture;
	class depth_stencil_view;
	class viewport;

	class skybox_pass : public pulsar::rg::pass
	{
	private:
		pulsar::vert_shader *mp_skybox_vs = NULL;
		pulsar::frag_shader *mp_skybox_fs = NULL;
		pulsar::depth_stencil_state *mp_ds_state = NULL;
		pulsar::sampler *mp_sampler = NULL;
		pulsar::input_layout *mp_input_layout = NULL;

		pulsar::render_texture *mp_hdr_buffer = NULL;
		pulsar::depth_stencil_view *mp_ds_view = NULL;
		pulsar::viewport *mp_viewport = NULL;

		pulsar::rg::buffer_input<pulsar::render_texture> *mp_hdr_buffer_input = NULL;
		pulsar::rg::buffer_source<pulsar::render_texture> *mp_hdr_buffer_source = NULL;

		pulsar::rg::buffer_input<pulsar::depth_stencil_view> *mp_ds_view_input = NULL;
		pulsar::rg::buffer_source<pulsar::depth_stencil_view> *mp_ds_view_source = NULL;

		pulsar::rg::bindable_input<pulsar::viewport> *mp_viewport_input = NULL;

	public:
		skybox_pass &operator=(const skybox_pass&) = delete;
		skybox_pass &operator=(skybox_pass&&) = delete;
		skybox_pass(const skybox_pass&) = delete;
		skybox_pass(skybox_pass&&) = delete;
		skybox_pass() = delete;
		skybox_pass(const std::string &name);
		~skybox_pass();

		void	validate() const override;
		void	execute() override;
	};
}
