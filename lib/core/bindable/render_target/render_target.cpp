
#include "render_target.h"


void		PULSAR::RENDER_TARGET::copy_assign(const RENDER_TARGET &rt)
{
	this->swap_chain = rt.swap_chain;
	this->back_buffer_texture = rt.back_buffer_texture;
	this->back_buffer = rt.back_buffer;

	if (this->swap_chain)
		this->swap_chain->AddRef();
	if (this->back_buffer_texture)
		this->back_buffer_texture->AddRef();
	if (this->back_buffer)
		this->back_buffer->AddRef();
}


PULSAR::RENDER_TARGET		&PULSAR::RENDER_TARGET::operator=(const RENDER_TARGET &rt)
{
	if (this->swap_chain != rt.swap_chain)
		this->remove_swap_chain();
	if (this->back_buffer_texture != rt.back_buffer_texture)
		this->remove_back_buffer_texture();
	if (this->back_buffer != rt.back_buffer)
		this->remove_back_buffer();

	this->copy_assign(rt);

	return (*this);
}

PULSAR::RENDER_TARGET::RENDER_TARGET(const RENDER_TARGET &rt) : PULSAR::BINDABLE()
{
	this->type = PULSAR::BINDABLE_TYPE::RENDER_TARGET;
	this->copy_assign(rt);
}

PULSAR::RENDER_TARGET::RENDER_TARGET() : PULSAR::BINDABLE()
{
	this->type = PULSAR::BINDABLE_TYPE::RENDER_TARGET;
}

PULSAR::RENDER_TARGET::RENDER_TARGET(HWND hwnd, BOOL windowed) : PULSAR::BINDABLE()
{
	this->type = PULSAR::BINDABLE_TYPE::RENDER_TARGET;
	this->set_rt_memory(hwnd, windowed);
}

PULSAR::RENDER_TARGET::~RENDER_TARGET()
{
	this->remove_rt_memory();
}
