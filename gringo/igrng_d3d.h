#pragma once

#include "grng_d3d.h"


class igrng_d3d
{
protected:
	static ID3D11Device				*device;
	static ID3D11DeviceContext		*device_context;

private:
	void		init_d3d()
	{
		igrng_d3d::device = GRNG_D3D::get_device();
		igrng_d3d::device_context = GRNG_D3D::get_device_context();
	}

public:
	igrng_d3d(const igrng_d3d &i) = delete;
	igrng_d3d(igrng_d3d &&i) = delete;
	igrng_d3d()
	{
		this->init_d3d();
	}
};

using IGRNG_D3D = igrng_d3d;
