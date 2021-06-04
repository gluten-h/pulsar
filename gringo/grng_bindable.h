#pragma once

#include "igrng_d3d.h"


class grng_bindable : public IGRNG_D3D
{
public:
	grng_bindable() : IGRNG_D3D(){ }
	virtual void		bind() = 0;
	virtual void		destroy() = 0;
};

using GRNG_BINDABLE = grng_bindable;
