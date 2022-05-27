#pragma once

#include "light.h"


namespace pulsar
{
	class dir_light : public pulsar::light
	{
	private:
		XMFLOAT3 m_color = XMFLOAT3(1.0f, 1.0f, 1.0f);

	public:
		dir_light &operator=(const dir_light&) = delete;
		dir_light &operator=(dir_light&&) = delete;
		dir_light(const dir_light&) = delete;
		dir_light(dir_light&&) = delete;
		dir_light();
		dir_light(const XMFLOAT3 &color);
		~dir_light() = default;

		XMFLOAT3	&color();
	};
}
