#pragma once

#include "grng_rg_bindable_pass.h"
#include "grng_rg_buffer_input.h"
#include "grng_rg_buffer_source.h"


class grng_buffer_clear_pass : public GRNG_RG_BINDABLE_PASS
{
private:
	GRNG_BUFFER_RESOURCE	*buffer = NULL;

	GRNG_RG_BUFFER_INPUT<GRNG_BUFFER_RESOURCE>		input = GRNG_RG_BUFFER_INPUT<GRNG_BUFFER_RESOURCE>("buffer");
	GRNG_RG_BUFFER_SOURCE<GRNG_BUFFER_RESOURCE>		source = GRNG_RG_BUFFER_SOURCE<GRNG_BUFFER_RESOURCE>("buffer");

public:
	grng_buffer_clear_pass(){ }
	grng_buffer_clear_pass(const std::string &name) : GRNG_RG_BINDABLE_PASS(name)
	{
		this->register_input(this->input);
		this->register_source(this->source);
	}

	void		execute() override
	{
		this->buffer->clear();
	}
};

using GRNG_BUFFER_CLEAR_PASS = grng_buffer_clear_pass;
