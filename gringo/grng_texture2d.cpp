
#include "grng_texture2d.h"


void					grng_texture2d::copy_assign(const grng_texture2d &t)
{
	this->texture = t.texture;
	if (this->texture)
		this->texture->AddRef();
}


grng_texture2d			&grng_texture2d::operator=(const grng_texture2d &t)
{
	if (this->texture != t.texture)
		this->remove_texture_memory();
	this->copy_assign(t);

	return (*this);
}

grng_texture2d::grng_texture2d(const grng_texture2d &t) : GRNG_ID3D()
{
	this->copy_assign(t);
}

grng_texture2d::grng_texture2d() : GRNG_ID3D()
{

}

grng_texture2d::grng_texture2d(float width, float height, DXGI_FORMAT format, UINT bind_flags, UINT cpu_access_flags) : GRNG_ID3D()
{
	this->set_texture_memory(width, height, format, bind_flags, cpu_access_flags);
}

grng_texture2d::~grng_texture2d()
{
	this->remove_texture_memory();
}
