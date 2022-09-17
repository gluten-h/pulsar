#pragma once

#include "render_graph/pass.h"
#include "render_graph/async_input.h"
#include "render_graph/async_source.h"
#include "config/config.h"
#include "containers/array.h"
#include "light/light.h"


namespace pulsar
{
	class depth_stencil_state;
	class vert_shader;
	class frag_shader;
	class input_layout;
	class shadows_rq;

	class shadow_mapping_pass : public pulsar::rg::pass
	{
	private:
		pulsar::depth_stencil_state *mp_dss = NULL;
		pulsar::vert_shader *mp_shadow_mapping_vs = NULL;
		pulsar::frag_shader *mp_shadow_mapping_fs = NULL;
		pulsar::input_layout *mp_input_layout = NULL;
		pulsar::shadows_rq *mp_shadows_rq = NULL;

		pulsar::rg::async_input<pulsar::shadows_rq> *mp_shadows_rq_input = NULL;
		pulsar::rg::async_source<pulsar::shadows_rq> *mp_shadows_rq_source = NULL;

	public:
		shadow_mapping_pass &operator=(const shadow_mapping_pass&) = delete;
		shadow_mapping_pass &operator=(shadow_mapping_pass&&) = delete;
		shadow_mapping_pass(const shadow_mapping_pass&) = delete;
		shadow_mapping_pass(shadow_mapping_pass&&) = delete;
		shadow_mapping_pass() = delete;
		shadow_mapping_pass(const std::string &name);
		~shadow_mapping_pass();

		void	validate() const override;
		void	execute() override;
	};
}
