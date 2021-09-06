//#pragma once
//
//#include "rg_pass.h"
//#include "rg_buffer_input.h"
//#include "rg_buffer_source.h"
//#include "render_target.h"
//
//#include <string>
//
//
//class PRESENT_PASS : public PULSAR::RG_PASS
//{
//private:
//	PULSAR::RENDER_TARGET		*backbuffer = NULL;
//
//	PULSAR::RG_BUFFER_INPUT<PULSAR::RENDER_TARGET>		*input = PULSAR::RG_BUFFER_INPUT<PULSAR::RENDER_TARGET>::create("backbuffer");
//	PULSAR::RG_BUFFER_SOURCE<PULSAR::RENDER_TARGET>		*source = PULSAR::RG_BUFFER_SOURCE<PULSAR::RENDER_TARGET>::create("backbuffer", this->backbuffer);
//
//public:
//	PRESENT_PASS(const std::string &name) : PULSAR::RG_PASS(name)
//	{
//		this->register_input(this->input);
//		this->register_source(this->source);
//	}
//	~PRESENT_PASS()
//	{
//		this->input->destroy();
//		this->source->destroy();
//	}
//
//	static PRESENT_PASS		*create(const std::string &name)
//	{
//		return ((PRESENT_PASS*)PULSAR::RG_COMPONENT::add_to_manager(new PRESENT_PASS(name)));
//	}
//
//	void	execute() override
//	{
//		this->backbuffer->present();
//	}
//};
