
#include "render_texture.h"


void		PULSAR::RENDER_TEXTURE::copy_assign(const RENDER_TEXTURE &rt)
{
	this->texture_rtv = rt.texture_rtv;
	this->texture_srv = rt.texture_srv;
	this->slot = slot;
	if (this->texture_rtv)
		this->texture_rtv->AddRef();
	if (this->texture_srv)
		this->texture_srv->AddRef();
}


PULSAR::RENDER_TEXTURE		&PULSAR::RENDER_TEXTURE::operator=(const RENDER_TEXTURE &rt)
{
	if (this->texture_rtv != rt.texture_rtv)
		this->remove_rtv();
	if (this->texture_srv != rt.texture_srv)
		this->remove_srv();

	this->copy_assign(rt);

	return (*this);
}

PULSAR::RENDER_TEXTURE::RENDER_TEXTURE(const RENDER_TEXTURE &rt) : PULSAR::BINDABLE()
{
	this->type = PULSAR::BINDABLE_TYPE::RENDER_TEXTURE;
	this->copy_assign(rt);
}

PULSAR::RENDER_TEXTURE::RENDER_TEXTURE() : PULSAR::BINDABLE()
{
	this->type = PULSAR::BINDABLE_TYPE::RENDER_TEXTURE;
}

PULSAR::RENDER_TEXTURE::RENDER_TEXTURE(ID3D11Texture2D *texture, UINT slot) : PULSAR::BINDABLE()
{
	this->type = PULSAR::BINDABLE_TYPE::RENDER_TEXTURE;

	this->set_rt_memory(texture);
	this->set_slot(slot);
}

PULSAR::RENDER_TEXTURE::~RENDER_TEXTURE()
{
	this->remove_rt_memory();
}
