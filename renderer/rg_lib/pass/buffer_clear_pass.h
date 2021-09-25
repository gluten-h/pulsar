#pragma once

#include "rg_pass.h"
#include "rg_buffer_input.h"
#include "rg_buffer_source.h"

#include <string>


namespace PULSAR
{
	class BUFFER_CLEAR_PASS : public PULSAR::RG_PASS
	{
	private:
		PULSAR::RENDER_TARGET		*backbuffer = NULL;

		PULSAR::RG_BUFFER_INPUT<PULSAR::RENDER_TARGET>	*input = PULSAR::RG_BUFFER_INPUT<PULSAR::RENDER_TARGET>::create("backbuffer", this->backbuffer);
		PULSAR::RG_BUFFER_SOURCE<PULSAR::RENDER_TARGET>	*source = PULSAR::RG_BUFFER_SOURCE<PULSAR::RENDER_TARGET>::create("backbuffer", this->backbuffer);

	public:
		BUFFER_CLEAR_PASS(const std::string &name) : PULSAR::RG_PASS(name)
		{
			this->register_input(this->input);
			this->register_source(this->source);
		}
		~BUFFER_CLEAR_PASS()
		{
			this->input->destroy();
			this->source->destroy();
		}

		static BUFFER_CLEAR_PASS	*create(const std::string &name)
		{
			return ((BUFFER_CLEAR_PASS*)PULSAR::RG_COMPONENT::add_to_manager(new BUFFER_CLEAR_PASS(name)));
		}

		void	execute() override
		{
			this->backbuffer->clear();
		}
	};
}
