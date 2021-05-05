#pragma once

#include "igrng_d3d.h"


class grng_drawable : public IGRNG_D3D
{
public:
	grng_drawable(const grng_drawable &d) = delete;
	grng_drawable(grng_drawable &&d) = delete;
	grng_drawable() : IGRNG_D3D()
	{

	}

	virtual void		draw() = 0;
};

using GRNG_DRAWABLE = grng_drawable;
