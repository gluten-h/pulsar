
#include "grng_point_light.h"


void					grng_point_light::copy_assign(const grng_point_light &l)
{
	this->pos = l.pos;
	this->color = l.color;

	this->const_att = l.const_att;
	this->linear_att = l.linear_att;
	this->quad_att = l.quad_att;
}


grng_point_light		&grng_point_light::operator=(const grng_point_light &l)
{
	this->copy_assign(l);

	return (*this);
}

grng_point_light::grng_point_light(const grng_point_light &l) : GRNG_LIGHT()
{
	this->type = GRNG_ENTITY_TYPE::POINT_LIGHT;
	this->light_type = GRNG_LIGHT_TYPE::POINT;
	this->copy_assign(l);
}

grng_point_light::grng_point_light() : GRNG_LIGHT()
{
	this->type = GRNG_ENTITY_TYPE::POINT_LIGHT;
	this->light_type = GRNG_LIGHT_TYPE::POINT;
}

grng_point_light::grng_point_light(const XMFLOAT3 &pos, const XMFLOAT3 &color, float const_att, float linear_att, float quad_att) : GRNG_LIGHT()
{
	this->type = GRNG_ENTITY_TYPE::POINT_LIGHT;
	this->light_type = GRNG_LIGHT_TYPE::POINT;
	this->set_params(pos, color, const_att, linear_att, quad_att);
}

grng_point_light::~grng_point_light()
{
	this->destroy();
}
