
#include "dir_light.h"


void		PULSAR::DIR_LIGHT::copy_assign(const DIR_LIGHT &l)
{
	this->dir = l.dir;
	this->color = l.color;
}


PULSAR::DIR_LIGHT		&PULSAR::DIR_LIGHT::operator=(const DIR_LIGHT &l)
{
	this->copy_assign(l);

	return (*this);
}

PULSAR::DIR_LIGHT::DIR_LIGHT(const DIR_LIGHT &l) : PULSAR::LIGHT()
{
	this->type = PULSAR::ENTITY_TYPE::DIR_LIGHT;
	this->light_type = PULSAR::LIGHT_TYPE::DIR;
	this->copy_assign(l);
}

PULSAR::DIR_LIGHT::DIR_LIGHT() : PULSAR::LIGHT()
{
	this->type = PULSAR::ENTITY_TYPE::DIR_LIGHT;
	this->light_type = PULSAR::LIGHT_TYPE::DIR;
}

PULSAR::DIR_LIGHT::DIR_LIGHT(const XMFLOAT3 &dir, const XMFLOAT3 &color) : PULSAR::LIGHT()
{
	this->type = PULSAR::ENTITY_TYPE::DIR_LIGHT;
	this->light_type = PULSAR::LIGHT_TYPE::DIR;
	this->set_params(dir, color);
}

PULSAR::DIR_LIGHT::~DIR_LIGHT()
{
	this->destroy();
}
