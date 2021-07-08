
#include "grng_texture.h"


void			grng_texture::copy_assign(const grng_texture &t)
{
	this->texture_srv = t.texture_srv;
	this->slot = t.slot;
	if (this->texture_srv)
		this->texture_srv->AddRef();
}


grng_texture	&grng_texture::operator=(const grng_texture &t)
{
	if (this->texture_srv != t.texture_srv)
		this->remove_texture_memory();
	this->copy_assign(t);

	return (*this);
}

grng_texture::grng_texture(const grng_texture &t) : GRNG_BINDABLE()
{
	this->copy_assign(t);
}

grng_texture::grng_texture() : GRNG_BINDABLE()
{
	this->type = GRNG_BINDABLE_TYPE::TEXTURE;
}

grng_texture::grng_texture(const LPCWSTR file, UINT slot) : GRNG_BINDABLE()
{
	this->type = GRNG_BINDABLE_TYPE::TEXTURE;

	this->set_texture_memory(file);
	this->set_slot(slot);
}

grng_texture::~grng_texture()
{
	this->remove_texture_memory();
}
