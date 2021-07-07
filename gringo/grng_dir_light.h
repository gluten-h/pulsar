#pragma once

#include "grng_light.h"


class grng_dir_light : public GRNG_LIGHT
{
private:
	XMFLOAT3		dir = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3		color = XMFLOAT3(1.0f, 1.0f, 1.0f);


	void		set_params(const XMFLOAT3 &dir, const XMFLOAT3 &color)
	{
		XMVECTOR dir_vec = XMVector3NormalizeEst(XMVectorSet(dir.x, dir.y, dir.z, 1.0f));

		this->dir = XMFLOAT3(XMVectorGetX(dir_vec), XMVectorGetY(dir_vec), XMVectorGetZ(dir_vec));
		this->color = color;
	}

public:
	void		operator=(const grng_dir_light &l)
	{
		this->dir = l.dir;
		this->color = l.color;
	}

	grng_dir_light() :GRNG_LIGHT()
	{
		this->type = GRNG_LIGHT_TYPE::DIR;
	}
	grng_dir_light(const XMFLOAT3 &dir, const XMFLOAT3 &color) : GRNG_LIGHT()
	{
		this->type = GRNG_LIGHT_TYPE::DIR;
		this->set_params(dir, color);
	}


	void		set(const XMFLOAT3 &dir, const XMFLOAT3 &color)
	{
		this->set_params(dir, color);
	}

	void		set_dir(const XMFLOAT3 &dir)
	{
		this->dir = dir;
	}

	void		set_color(const XMFLOAT3 &color)
	{
		this->color = color;
	}


	XMFLOAT3	&get_dir()
	{
		return (this->dir);
	}

	XMFLOAT3	&get_color()
	{
		return (this->color);
	}


	void		set_shader_light(GRNG_SHADER_LIGHT &sl) override
	{
		sl.type = (int)this->type;

		sl.dir = this->dir;
		sl.color = this->color;
	}

	static GRNG_LIGHT		*create_manager_ptr()
	{
		grng_dir_light *light = new grng_dir_light;

		return (light);
	}
};

using GRNG_DIR_LIGHT = grng_dir_light;
