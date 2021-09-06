#pragma once

#include "pulsar_d3d.h"


namespace PULSAR
{
	class PULSAR_ID3D
	{
	private:
		static bool						is_initialized;

	protected:
		static IDXGIFactory* idxgi_factory;
		static ID3D11Device* device;
		static ID3D11DeviceContext* device_context;

	private:
		void		init_d3d()
		{
			this->is_initialized = true;
			PULSAR_D3D::create();

			PULSAR_ID3D::idxgi_factory = PULSAR_D3D::get_idxgi_factory();
			PULSAR_ID3D::device = PULSAR_D3D::get_device();
			PULSAR_ID3D::device_context = PULSAR_D3D::get_device_context();
		}

	public:
		PULSAR_ID3D()
		{
			if (PULSAR_ID3D::is_initialized)
				return;

			this->init_d3d();
		}
	};
}
