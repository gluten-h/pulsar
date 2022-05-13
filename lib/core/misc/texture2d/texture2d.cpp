//
//#include "texture2d.h"
//
//
//void	PULSAR::texture2d::copy_assign(const PULSAR::texture2d &t)
//{
//	this->mp_texture = t.mp_texture;
//	if (this->mp_texture)
//		this->mp_texture->AddRef();
//}
//
//
//PULSAR::texture2d	&PULSAR::texture2d::operator=(const PULSAR::texture2d &t)
//{
//	if (this->mp_texture != t.mp_texture)
//		this->free();
//	this->copy_assign(t);
//
//	return (*this);
//}
//
//PULSAR::texture2d::texture2d(const PULSAR::texture2d &t)
//{
//	this->copy_assign(t);
//}
//
//PULSAR::texture2d::texture2d(){ }
//
//PULSAR::texture2d::texture2d(UINT width, UINT height, DXGI_FORMAT format, UINT bind_flags, UINT cpu_access_flags)
//{
//	this->create_texture2d(width, height, format, bind_flags, cpu_access_flags);
//}
//
//PULSAR::texture2d::~texture2d()
//{
//	this->free();
//}
