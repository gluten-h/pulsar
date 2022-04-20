
#include "texture2d.h"


void		PULSAR::TEXTURE2D::copy_assign(const PULSAR::TEXTURE2D &t)
{
	this->texture = t.texture;
	if (this->texture)
		this->texture->AddRef();
}


PULSAR::TEXTURE2D		&PULSAR::TEXTURE2D::operator=(const PULSAR::TEXTURE2D &t)
{
	if (this->texture != t.texture)
		this->remove_texture_memory();
	this->copy_assign(t);

	return (*this);
}

PULSAR::TEXTURE2D::TEXTURE2D(const PULSAR::TEXTURE2D &t)
{
	this->copy_assign(t);
}

PULSAR::TEXTURE2D::TEXTURE2D(){ }

PULSAR::TEXTURE2D::TEXTURE2D(float width, float height, DXGI_FORMAT format, UINT bind_flags, UINT cpu_access_flags)
{
	this->set_texture_memory(width, height, format, bind_flags, cpu_access_flags);
}

PULSAR::TEXTURE2D::~TEXTURE2D()
{
	this->remove_texture_memory();
}
