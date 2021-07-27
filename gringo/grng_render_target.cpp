
#include "grng_render_target.h"


void		grng_render_target::copy_assign(const grng_render_target &rt)
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


grng_render_target		&grng_render_target::operator=(const grng_render_target &rt)
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

grng_render_target::grng_render_target(const grng_render_target &rt) : GRNG_BINDABLE()
{
	this->type = GRNG_BINDABLE_TYPE::RENDER_TARGET;
	this->copy_assign(rt);
}

grng_render_target::grng_render_target() : GRNG_BINDABLE()
{
	this->type = GRNG_BINDABLE_TYPE::RENDER_TARGET;
}

grng_render_target::grng_render_target(HWND hwnd, BOOL windowed) : GRNG_BINDABLE()
{
	this->type = GRNG_BINDABLE_TYPE::RENDER_TARGET;
	this->set_rt_memory(hwnd, windowed);
}

grng_render_target::~grng_render_target()
{
	this->remove_rt_memory();
}
