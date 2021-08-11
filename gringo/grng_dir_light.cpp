
#include "grng_dir_light.h"


void				grng_dir_light::copy_assign(const grng_dir_light &l)
{
	this->dir = l.dir;
	this->color = l.color;
}


grng_dir_light		&grng_dir_light::operator=(const grng_dir_light &l)
{
	this->copy_assign(l);

	return (*this);
}

grng_dir_light::grng_dir_light(const grng_dir_light &l) : GRNG_LIGHT()
{
	this->type = GRNG_ENTITY_TYPE::DIR_LIGHT;
	this->light_type = GRNG_LIGHT_TYPE::DIR;
	this->copy_assign(l);
}

grng_dir_light::grng_dir_light() :GRNG_LIGHT()
{
	this->type = GRNG_ENTITY_TYPE::DIR_LIGHT;
	this->light_type = GRNG_LIGHT_TYPE::DIR;
}

grng_dir_light::grng_dir_light(const XMFLOAT3 &dir, const XMFLOAT3 &color) : GRNG_LIGHT()
{
	this->type = GRNG_ENTITY_TYPE::DIR_LIGHT;
	this->light_type = GRNG_LIGHT_TYPE::DIR;
	this->set_params(dir, color);
}

grng_dir_light::~grng_dir_light()
{
	this->destroy();
}
