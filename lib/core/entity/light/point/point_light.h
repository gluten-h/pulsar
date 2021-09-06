#pragma once

#include "light.h"
#include "scene.h"


namespace PULSAR
{
	class POINT_LIGHT : public PULSAR::LIGHT
	{
	private:
		friend class PULSAR::LIGHT_MANAGER;

	private:
		XMFLOAT3	pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
		XMFLOAT3	color = XMFLOAT3(1.0f, 1.0f, 1.0f);

		float	const_att = 1.0f;
		float	linear_att = 0.14f;
		float	quad_att = 0.07f;


		void	set_params(const XMFLOAT3 &pos, const XMFLOAT3 &color, float const_att, float linear_att, float quad_att);
		void	set_shader_light(SHADER_LIGHT &sl) override;

		void	copy_assign(const POINT_LIGHT &l);

	public:
		POINT_LIGHT &operator=(const POINT_LIGHT &l);
		POINT_LIGHT(const POINT_LIGHT &l);
		POINT_LIGHT();
		POINT_LIGHT(const XMFLOAT3 &pos, const XMFLOAT3 &color, float const_att = 1.0f, float linear_att = 0.14f, float quad_att = 0.07f);
		~POINT_LIGHT();

		void	set(const XMFLOAT3 &pos, const XMFLOAT3 &color, float const_att, float linear_att, float quad_att);
		void	set_pos(const XMFLOAT3 &pos);
		void	set_color(const XMFLOAT3 &color);
		void	set_attenuation(float const_att, float linear_att, float quad_att);
		void	set_const_attenuation(float const_att);
		void	set_linear_attenuation(float linear_att);
		void	set_quad_attenuation(float quad_att);

		XMFLOAT3	 &get_pos();
		XMFLOAT3	 &get_color();

		static POINT_LIGHT		*create();
		void					destroy();
	};
}
