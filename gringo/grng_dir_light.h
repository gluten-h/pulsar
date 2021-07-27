#pragma once

#include "grng_light.h"


class grng_dir_light : public GRNG_LIGHT
{
private:
	friend class grng_light_manager;
	friend class grng_manager_ptr;

private:
	XMFLOAT3		dir = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3		color = XMFLOAT3(1.0f, 1.0f, 1.0f);


	void		set_params(const XMFLOAT3 &dir, const XMFLOAT3 &color);
	void		set_shader_light(GRNG_SHADER_LIGHT &sl) override;

	static GRNG_LIGHT	*create_manager_ptr();

	void				copy_assign(const grng_dir_light &l);

public:
	grng_dir_light		&operator=(const grng_dir_light &l);
	grng_dir_light(const grng_dir_light &l);
	grng_dir_light();
	grng_dir_light(const XMFLOAT3 &dir, const XMFLOAT3 &color);

	void		set(const XMFLOAT3 &dir, const XMFLOAT3 &color);
	void		set_dir(const XMFLOAT3 &dir);
	void		set_color(const XMFLOAT3 &color);

	XMFLOAT3	&get_dir();
	XMFLOAT3	&get_color();
};

using GRNG_DIR_LIGHT = grng_dir_light;
