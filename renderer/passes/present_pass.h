#pragma once

#include "rg/pass.h"
#include "rg/buffer_input.h"
#include "rg/buffer_source.h"


namespace PULSAR
{
	class framebuffer;

	class present_pass : public PULSAR::rg::pass
	{
	private:
		PULSAR::framebuffer *mp_framebuffer = NULL;

		PULSAR::rg::buffer_input<PULSAR::framebuffer> *mp_framebuffer_input = NULL;
		PULSAR::rg::buffer_source<PULSAR::framebuffer> *mp_frambuffer_source = NULL;

	public:
		present_pass &operator=(const present_pass&) = delete;
		present_pass &operator=(present_pass&&) = delete;
		present_pass(const present_pass&) = delete;
		present_pass(present_pass&&) = delete;
		present_pass() = delete;
		present_pass(const std::string &name);
		~present_pass();

		void	validate() const override;
		void	execute() override;
	};
}
