
#include "grng_render_texture.h"


void		grng_render_texture::copy_assign(const grng_render_texture &rt)
{
	this->texture_rtv = rt.texture_rtv;
	this->texture_srv = rt.texture_srv;
	this->slot = slot;
	if (this->texture_rtv)
		this->texture_rtv->AddRef();
	if (this->texture_srv)
		this->texture_srv->AddRef();
}


grng_render_texture		&grng_render_texture::operator=(const grng_render_texture &rt)
{
	if (this->texture_rtv != rt.texture_rtv)
		this->remove_rtv();
	if (this->texture_srv != rt.texture_srv)
		this->remove_srv();

	this->copy_assign(rt);

	return (*this);
}

grng_render_texture::grng_render_texture(const grng_render_texture &rt) : GRNG_BINDABLE()
{
	this->type = GRNG_BINDABLE_TYPE::RENDER_TEXTURE;
	this->copy_assign(rt);
}

grng_render_texture::grng_render_texture() : GRNG_BINDABLE()
{
	this->type = GRNG_BINDABLE_TYPE::RENDER_TEXTURE;
}

grng_render_texture::grng_render_texture(ID3D11Texture2D *texture, UINT slot) : GRNG_BINDABLE()
{
	this->type = GRNG_BINDABLE_TYPE::RENDER_TEXTURE;

	this->set_rt_memory(texture);
	this->set_slot(slot);
}

grng_render_texture::~grng_render_texture()
{
	this->remove_rt_memory();
}
