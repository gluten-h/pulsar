#pragma once

//#include "rg_pass.h"
//#include "rg_buffer_input.h"
//#include "rg_buffer_source.h"
//
//#include <string>
//
//
//namespace PULSAR
//{
//	class BUFFER_CLEAR_PASS : public PULSAR::RG_PASS
//	{
//	private:
//		PULSAR::RENDER_TARGET		*backbuffer = NULL;
//
//		PULSAR::RG_BUFFER_INPUT<PULSAR::RENDER_TARGET>	*input = PULSAR::RG_BUFFER_INPUT<PULSAR::RENDER_TARGET>::create("backbuffer", this->backbuffer);
//		PULSAR::RG_BUFFER_SOURCE<PULSAR::RENDER_TARGET>	*source = PULSAR::RG_BUFFER_SOURCE<PULSAR::RENDER_TARGET>::create("backbuffer", this->backbuffer);
//
//	public:
//		BUFFER_CLEAR_PASS(const std::string &name) : PULSAR::RG_PASS(name)
//		{
//			this->register_input(this->input);
//			this->register_source(this->source);
//		}
//		~BUFFER_CLEAR_PASS()
//		{
//			this->input->destroy();
//			this->source->destroy();
//		}
//
//		static BUFFER_CLEAR_PASS	*create(const std::string &name)
//		{
//			return ((BUFFER_CLEAR_PASS*)PULSAR::RG_COMPONENT::add_to_manager(new BUFFER_CLEAR_PASS(name)));
//		}
//
//		void	execute() override
//		{
//			this->backbuffer->clear();
//		}
//	};
//}


#include "rg/pass.h"
#include "rg/buffer_input.h"
#include "rg/buffer_source.h"


namespace PULSAR
{
	class framebuffer;

	class clear_buffer_pass : public PULSAR::rg::pass
	{
	private:
		PULSAR::framebuffer *mp_framebuffer = NULL;

		PULSAR::rg::buffer_input<PULSAR::framebuffer> *mp_framebuffer_input = NULL;
		PULSAR::rg::buffer_source<PULSAR::framebuffer> *mp_frambuffer_source = NULL;

	public:
		clear_buffer_pass &operator=(const clear_buffer_pass&) = delete;
		clear_buffer_pass &operator=(clear_buffer_pass&&) = delete;
		clear_buffer_pass(const clear_buffer_pass&) = delete;
		clear_buffer_pass(clear_buffer_pass&&) = delete;
		clear_buffer_pass() = delete;
		clear_buffer_pass(const std::string &name);
		~clear_buffer_pass();

		void	validate() const override;
		void	execute() override;
	};
}
