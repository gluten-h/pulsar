
#include "grng_point_light.h"


void			grng_point_light::set_params(const XMFLOAT3 &pos, const XMFLOAT3 &color, float const_att, float linear_att, float quad_att)
{
	this->pos = pos;
	this->color = color;

	this->const_att = const_att;
	this->linear_att = linear_att;
	this->quad_att = quad_att;
}

void			grng_point_light::set_shader_light(GRNG_SHADER_LIGHT &sl)
{
	sl.type = (int)this->type;

	sl.pos = this->pos;
	sl.color = this->color;

	sl.attenuation = XMFLOAT4(this->const_att, this->linear_att, this->quad_att, 1.0f);
}

GRNG_LIGHT		*grng_point_light::create_manager_ptr()
{
	grng_point_light *light = new grng_point_light;

	return (light);
}

void			grng_point_light::set(const XMFLOAT3 &pos, const XMFLOAT3 &color, float const_att, float linear_att, float quad_att)
{
	this->set_params(pos, color, const_att, linear_att, quad_att);
}

void			grng_point_light::set_pos(const XMFLOAT3 &pos)
{
	this->pos = pos;
}

void			grng_point_light::set_color(const XMFLOAT3 &color)
{
	this->color = color;
}

void			grng_point_light::set_attenuation(float const_att, float linear_att, float quad_att)
{
	this->const_att = const_att;
	this->linear_att = linear_att;
	this->quad_att = quad_att;
}

void			grng_point_light::set_const_attenuation(float const_att)
{
	this->const_att = const_att;
}

void			grng_point_light::set_linear_attenuation(float linear_att)
{
	this->linear_att = linear_att;
}

void			grng_point_light::set_quad_attenuation(float quad_att)
{
	this->quad_att = quad_att;
}
