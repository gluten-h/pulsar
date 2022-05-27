
#include "point_light.h"


pulsar::point_light::point_light() : pulsar::light(pulsar::LIGHT_TYPE::POINT)
{
	
}

pulsar::point_light::point_light(/*const XMFLOAT3 &pos, */const XMFLOAT3 &color, float const_att, float linear_att, float quad_att) : pulsar::light(pulsar::LIGHT_TYPE::POINT)
{
	//this->m_pos = pos;
	this->m_color = color;
	this->m_const_att = const_att;
	this->m_linear_att = linear_att;
	this->m_quad_att = quad_att;
}

//XMFLOAT3	&pulsar::point_light::position()
//{
//	return (this->m_pos);
//}

XMFLOAT3	&pulsar::point_light::color()
{
	return (this->m_color);
}

float	&pulsar::point_light::const_attenuation()
{
	return (this->m_const_att);
}

float	&pulsar::point_light::linear_attenuation()
{
	return (this->m_linear_att);
}

float	&pulsar::point_light::quad_attenuation()
{
	return (this->m_quad_att);
}
