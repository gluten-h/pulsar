
#include "present_pass.h"
#include "gfx_resources/framebuffer.h"
#include "config/config.h"
#include "exceptions/rg_exception.h"


pulsar::present_pass::present_pass(const std::string &name) : pulsar::rg::pass(name)
{
	this->mp_framebuffer_input = new pulsar::rg::sync_input<pulsar::framebuffer>(pulsar::RG_G_FRAMEBUFFER, this->mp_framebuffer);
	this->register_input(this->mp_framebuffer_input);
}

pulsar::present_pass::~present_pass()
{
	delete this->mp_framebuffer_input;
}

void	pulsar::present_pass::validate() const
{
	if (!this->mp_framebuffer)
		THROW_RG_EXC("Framebuffer isn't bound");
}

void	pulsar::present_pass::execute()
{
	this->mp_framebuffer->present();
}
