#pragma once

#include "grng_d3d.h"


class igrng_d3d : public GRNG_D3D
{
private:
	void		init_d3d()
	{
		GRNG_D3D::create();
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
