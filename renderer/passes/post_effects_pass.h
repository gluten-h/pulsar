#pragma once

#include "passes/fullscreen_pass.h"
#include "render_graph/sync_input.h"
#include "render_graph/sync_source.h"
#include "render_graph/async_input.h"


namespace pulsar
{
	class frag_shader;
	class sampler;
	class framebuffer;
	class render_texture;

	class post_effects_pass : public pulsar::fullscreen_pass
	{
	private:
		pulsar::frag_shader *mp_post_effects_fs = NULL;
		pulsar::sampler *mp_sampler = NULL;

		pulsar::framebuffer *mp_framebuffer = NULL;
		pulsar::render_texture *mp_hdr_buffer = NULL;

		pulsar::rg::sync_input<pulsar::framebuffer> *mp_frambuffer_input = NULL;
		pulsar::rg::sync_source<pulsar::framebuffer> *mp_framebuffer_source = NULL;

		pulsar::rg::sync_input<pulsar::render_texture> *mp_hdr_buffer_input = NULL;
		pulsar::rg::sync_source<pulsar::render_texture> *mp_hdr_buffer_source = NULL;

	public:
		post_effects_pass &operator=(const post_effects_pass&) = delete;
		post_effects_pass &operator=(post_effects_pass&&) = delete;
		post_effects_pass(const post_effects_pass&) = delete;
		post_effects_pass(post_effects_pass&&) = delete;
		post_effects_pass() = delete;
		post_effects_pass(const std::string &name);
		~post_effects_pass();

		void	validate() const override;
		void	execute() override;
	};
}
