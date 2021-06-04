#pragma once

#include "grng_light.h"


class grng_point_light : public GRNG_LIGHT
{
private:
	XMFLOAT3		pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3		color = XMFLOAT3(1.0f, 1.0f, 1.0f);
	
	float			const_att = 1.0f;
	float			linear_att = 1.0f;
	float			quad_att = 1.0f;


	void		set_params(const XMFLOAT3 &pos, const XMFLOAT3 &color, float const_att, float linear_att, float quad_att)
	{
		this->pos = pos;
		this->color = color;

		this->const_att = const_att;
		this->linear_att = linear_att;
		this->quad_att = quad_att;
	}

public:
	grng_point_light(const XMFLOAT3 &pos, const XMFLOAT3 &color, float const_att, float linear_att, float quad_att) : GRNG_LIGHT()
	{
		this->type = GRNG_LIGHT_TYPE_POINT;
		this->set_params(pos, color, const_att, linear_att, quad_att);
	}


	void		set(const XMFLOAT3 &pos, const XMFLOAT3 &color, float const_att, float linear_att, float quad_att)
	{
		this->set_params(pos, color, const_att, linear_att, quad_att);
	}

	void		set_pos(const XMFLOAT3 &pos)
	{
		this->pos = pos;
	}

	void		set_color(const XMFLOAT3 &color)
	{
		this->color = color;
	}

	void		set_attenuation(float const_att, float linear_att, float quad_att)
	{
		this->const_att = const_att;
		this->linear_att = linear_att;
		this->quad_att = quad_att;
	}

	void		set_const_attenuation(float const_att)
	{
		this->const_att = const_att;
	}

	void		set_linear_attenuation(float linear_att)
	{
		this->linear_att = linear_att;
	}

	void		set_quad_attenuation(float quad_att)
	{
		this->quad_att = quad_att;
	}


	void		set_shader_light(GRNG_SHADER_LIGHT &sl) override
	{
		sl.type = this->type;

		sl.pos = this->pos;
		sl.color = this->color;

		sl.attenuation = XMFLOAT4(this->const_att, this->linear_att, this->quad_att, 1.0f);
	}
};

using GRNG_POINT_LIGHT = grng_point_light;
