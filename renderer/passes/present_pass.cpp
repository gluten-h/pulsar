
#include "present_pass.h"
#include "framebuffer/framebuffer.h"
#include "config/render_graph.h"
#include "exceptions/rg_exception.h"


PULSAR::present_pass::present_pass(const std::string &name) : PULSAR::rg::pass(name)
{
	this->mp_framebuffer_input = new PULSAR::rg::buffer_input<PULSAR::framebuffer>(RG_G_FRAMEBUFFER, this->mp_framebuffer);
	this->mp_frambuffer_source = new PULSAR::rg::buffer_source<PULSAR::framebuffer>(RG_G_FRAMEBUFFER, this->mp_framebuffer);

	this->register_input(this->mp_framebuffer_input);
	this->register_source(this->mp_frambuffer_source);
}

PULSAR::present_pass::~present_pass()
{
	delete this->mp_framebuffer_input;
	delete this->mp_frambuffer_source;
}

void	PULSAR::present_pass::validate() const
{
	if (!this->mp_framebuffer)
		THROW_RG_EXC("Framebuffer isn't bound");
}

void	PULSAR::present_pass::execute()
{
	this->mp_framebuffer->present();
}
