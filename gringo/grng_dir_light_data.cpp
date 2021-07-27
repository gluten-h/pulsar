
#include "grng_dir_light.h"


void			grng_dir_light::set_params(const XMFLOAT3 &dir, const XMFLOAT3 &color)
{
	XMVECTOR dir_vec = XMVector3NormalizeEst(XMVectorSet(dir.x, dir.y, dir.z, 1.0f));

	this->dir = XMFLOAT3(XMVectorGetX(dir_vec), XMVectorGetY(dir_vec), XMVectorGetZ(dir_vec));
	this->color = color;
}

void			grng_dir_light::set_shader_light(GRNG_SHADER_LIGHT &sl)
{
	sl.type = (int)this->type;

	sl.dir = this->dir;
	sl.color = this->color;
}

GRNG_LIGHT		*grng_dir_light::create_manager_ptr()
{
	grng_dir_light *light = new grng_dir_light;

	return (light);
}

void			grng_dir_light::set(const XMFLOAT3 &dir, const XMFLOAT3 &color)
{
	this->set_params(dir, color);
}

void			grng_dir_light::set_dir(const XMFLOAT3 &dir)
{
	this->set_params(dir, this->color);
}

void			grng_dir_light::set_color(const XMFLOAT3 &color)
{
	this->color = color;
}
