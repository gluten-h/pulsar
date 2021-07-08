#pragma once

#include "grng_d3d.h"


class grng_id3d
{
private:
	static bool						is_initialized;

protected:
	static IDXGIFactory				*idxgi_factory;
	static ID3D11Device				*device;
	static ID3D11DeviceContext		*device_context;

private:
	void		init_d3d()
	{
		GRNG_D3D::create();

		grng_id3d::idxgi_factory = GRNG_D3D::get_idxgi_factory();
		grng_id3d::device = GRNG_D3D::get_device();
		grng_id3d::device_context = GRNG_D3D::get_device_context();
	}

public:
	grng_id3d()
	{
		if (grng_id3d::is_initialized)
			return;

		this->init_d3d();
	}
};

using GRNG_ID3D = grng_id3d;
