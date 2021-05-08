#pragma once

#include "igrng_d3d.h"
#include "grng_const_buffer.h"
#include "grng_components.h"

#include <memory>
#include <vector>


class grng_drawable : public IGRNG_D3D
{
protected:
	std::vector <GRNG_BINDABLE*>	bindables;

	static GRNG_VERT_TRANSFORM								vert_transform;
	static GRNG_VERT_CONST_BUFFER<GRNG_VERT_TRANSFORM>		transform_cbuffer;

public:
	grng_drawable(const grng_drawable &d) = delete;
	grng_drawable(grng_drawable &&d) = delete;
	grng_drawable() : IGRNG_D3D()
	{

	}

	void	add_bindable(GRNG_BINDABLE &bindable)
	{
		this->bindables.push_back(&bindable);
	}

	virtual void		draw() = 0;
};

using GRNG_DRAWABLE = grng_drawable;
