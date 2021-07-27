#pragma once

#include "grng_light.h"


class grng_point_light : public GRNG_LIGHT
{
private:
	friend class grng_light_manager;
	friend class grng_manager_ptr;

private:
	XMFLOAT3	pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3	color = XMFLOAT3(1.0f, 1.0f, 1.0f);
	
	float		const_att = 1.0f;
	float		linear_att = 0.14f;
	float		quad_att = 0.07f;


	void		set_params(const XMFLOAT3 &pos, const XMFLOAT3 &color, float const_att, float linear_att, float quad_att);
	void		set_shader_light(GRNG_SHADER_LIGHT &sl) override;

	static GRNG_LIGHT		*create_manager_ptr();

	void					copy_assign(const grng_point_light &l);

public:
	grng_point_light		&operator=(const grng_point_light &l);
	grng_point_light(const grng_point_light &l);
	grng_point_light();
	grng_point_light(const XMFLOAT3 &pos, const XMFLOAT3 &color, float const_att = 1.0f, float linear_att = 0.14f, float quad_att = 0.07f);

	void		set(const XMFLOAT3 &pos, const XMFLOAT3 &color, float const_att, float linear_att, float quad_att);
	void		set_pos(const XMFLOAT3 &pos);
	void		set_color(const XMFLOAT3 &color);
	void		set_attenuation(float const_att, float linear_att, float quad_att);
	void		set_const_attenuation(float const_att);
	void		set_linear_attenuation(float linear_att);
	void		set_quad_attenuation(float quad_att);

	XMFLOAT3	&get_pos();
	XMFLOAT3	&get_color();
};

using GRNG_POINT_LIGHT = grng_point_light;
