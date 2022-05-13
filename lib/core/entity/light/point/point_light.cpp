//
//#include "point_light.h"
//
//
//void		PULSAR::POINT_LIGHT::copy_assign(const POINT_LIGHT &l)
//{
//	this->pos = l.pos;
//	this->color = l.color;
//
//	this->const_att = l.const_att;
//	this->linear_att = l.linear_att;
//	this->quad_att = l.quad_att;
//}
//
//
//PULSAR::POINT_LIGHT		&PULSAR::POINT_LIGHT::operator=(const POINT_LIGHT &l)
//{
//	this->copy_assign(l);
//
//	return (*this);
//}
//
//PULSAR::POINT_LIGHT::POINT_LIGHT(const POINT_LIGHT &l) : PULSAR::LIGHT()
//{
//	this->type = PULSAR::ENTITY_TYPE::POINT_LIGHT;
//	this->light_type = PULSAR::LIGHT_TYPE::POINT;
//	this->copy_assign(l);
//}
//
//PULSAR::POINT_LIGHT::POINT_LIGHT() : PULSAR::LIGHT()
//{
//	this->type = PULSAR::ENTITY_TYPE::POINT_LIGHT;
//	this->light_type = PULSAR::LIGHT_TYPE::POINT;
//}
//
//PULSAR::POINT_LIGHT::POINT_LIGHT(const XMFLOAT3 &pos, const XMFLOAT3 &color, float const_att, float linear_att, float quad_att) : PULSAR::LIGHT()
//{
//	this->type = PULSAR::ENTITY_TYPE::POINT_LIGHT;
//	this->light_type = PULSAR::LIGHT_TYPE::POINT;
//	this->set_params(pos, color, const_att, linear_att, quad_att);
//}
//
//PULSAR::POINT_LIGHT::~POINT_LIGHT()
//{
//	this->destroy();
//}
