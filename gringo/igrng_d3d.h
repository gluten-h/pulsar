#pragma once

#include "grng_d3d.h"


class grng_id3d : protected GRNG_D3D
{
private:
	void		init_d3d()
	{
		GRNG_D3D::create();
	}

public:
	grng_id3d()
	{
		this->init_d3d();
	}
};

using GRNG_ID3D = grng_id3d;
