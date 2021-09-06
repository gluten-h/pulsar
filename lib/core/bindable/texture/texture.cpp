
#include "texture.h"


void		PULSAR::TEXTURE::copy_assign(const TEXTURE &t)
{
	this->texture2d = t.texture2d;
	this->texture_srv = t.texture_srv;
	this->slot = t.slot;

	if (this->texture2d)
		this->texture2d->AddRef();
	if (this->texture_srv)
		this->texture_srv->AddRef();
}


PULSAR::TEXTURE		&PULSAR::TEXTURE::operator=(const TEXTURE &t)
{
	if (this->texture2d != t.texture2d)
		this->remove_texture2d_memory();
	if (this->texture_srv != t.texture_srv)
		this->remove_texture_srv_memory();
	this->copy_assign(t);

	return (*this);
}

PULSAR::TEXTURE::TEXTURE(const TEXTURE &t) : PULSAR::BINDABLE()
{
	this->type = PULSAR::BINDABLE_TYPE::TEXTURE;
	this->copy_assign(t);
}

PULSAR::TEXTURE::TEXTURE() : PULSAR::BINDABLE()
{
	this->type = PULSAR::BINDABLE_TYPE::TEXTURE;
}

PULSAR::TEXTURE::TEXTURE(const LPCWSTR file, UINT slot) : PULSAR::BINDABLE()
{
	this->type = PULSAR::BINDABLE_TYPE::TEXTURE;

	this->set_texture_memory(file);
	this->set_slot(slot);
}

PULSAR::TEXTURE::~TEXTURE()
{
	this->remove_texture_memory();
}
