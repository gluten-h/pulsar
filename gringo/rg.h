#pragma once

#include "grng_render_graph.h"
#include "grng_buffer_clear_pass.h"


class grng_rg : public GRNG_RENDER_GRAPH
{
private:
	GRNG_BUFFER_CLEAR_PASS		clear_pass;

public:
	grng_rg()
	{
		this->clear_pass = GRNG_BUFFER_CLEAR_PASS("clear_rt");
		this->clear_pass.set_input_linkage("buffer", "~.backbuffer");
		this->add_pass(this->clear_pass);
	}
};
