#pragma once

#include "igrng_d3d.h"


class grng_bindable : public IGRNG_D3D
{
private:
	void	init_d3d()
	{
		grng_bindable::device = GRNG_D3D::get_device();
		grng_bindable::device_context = GRNG_D3D::get_device_context();
	}

public:
	grng_bindable() : IGRNG_D3D()
	{
		this->init_d3d();
	}
	virtual void		bind() = 0;
};

using GRNG_BINDABLE = grng_bindable;
