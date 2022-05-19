#pragma once

#include "render_graph/pass.h"
#include "render_graph/buffer_input.h"


namespace PULSAR
{
	class framebuffer;

	class present_pass : public PULSAR::rg::pass
	{
	private:
		PULSAR::framebuffer *mp_framebuffer = NULL;
		PULSAR::rg::buffer_input<PULSAR::framebuffer> *mp_framebuffer_input = NULL;

	public:
		present_pass &operator=(const present_pass&) = delete;
		present_pass &operator=(present_pass&&) = delete;
		present_pass(const present_pass&) = delete;
		present_pass(present_pass&&) = delete;
		present_pass() = delete;
		present_pass(const std::string &name);
		~present_pass();

		void	validate() const override;
		void	execute(float delta_time) override;
	};
}
