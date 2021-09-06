#pragma once

#include "light.h"
#include "scene.h"


namespace PULSAR
{
	class DIR_LIGHT : public PULSAR::LIGHT
	{
	private:
		friend class LIGHT_MANAGER;

	private:
		XMFLOAT3	dir = XMFLOAT3(0.0f, 0.0f, 0.0f);
		XMFLOAT3	color = XMFLOAT3(1.0f, 1.0f, 1.0f);


		void	set_params(const XMFLOAT3 &dir, const XMFLOAT3 &color);
		void	set_shader_light(SHADER_LIGHT &sl) override;

		void	copy_assign(const DIR_LIGHT &l);

	public:
		DIR_LIGHT	&operator=(const DIR_LIGHT &l);
		DIR_LIGHT(const DIR_LIGHT &l);
		DIR_LIGHT();
		DIR_LIGHT(const XMFLOAT3 &dir, const XMFLOAT3 &color);
		~DIR_LIGHT();

		void	set(const XMFLOAT3 &dir, const XMFLOAT3 &color);
		void	set_dir(const XMFLOAT3 &dir);
		void	set_color(const XMFLOAT3 &color);

		XMFLOAT3	 &get_dir();
		XMFLOAT3	 &get_color();

		static DIR_LIGHT	*create();
		void				destroy();
	};
}
