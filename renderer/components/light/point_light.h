#pragma once

#include "light.h"


namespace pulsar
{
	class point_light : public pulsar::light
	{
	private:
		//XMFLOAT3 m_pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
		XMFLOAT3 m_color = XMFLOAT3(1.0f, 1.0f, 1.0f);

		float m_const_att = 1.0f;
		float m_linear_att = 0.14f;
		float m_quad_att = 0.07f;

	public:
		point_light &operator=(const point_light&) = delete;
		point_light &operator=(point_light&&) = delete;
		point_light(const point_light&) = delete;
		point_light(point_light&&) = delete;
		point_light();
		point_light(/*const XMFLOAT3 &pos, */const XMFLOAT3 &color, float const_att = 1.0f, float linear_att = 0.14f, float quad_att = 0.07f);
		~point_light() = default;

		//XMFLOAT3	&position();
		XMFLOAT3	&color();
		float		&const_attenuation();
		float		&linear_attenuation();
		float		&quad_attenuation();
	};
}
