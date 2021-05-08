#pragma once

#include "grng_bindable.h"


class grng_sampler : public GRNG_BINDABLE
{
private:
	ID3D11SamplerState		*sampler = NULL;


	void		set_sampler_memory()
	{
		D3D11_SAMPLER_DESC sd;
		ZeroMemory(&sd, sizeof(D3D11_SAMPLER_DESC));
		sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

		HRESULT hr = this->device->CreateSamplerState(&sd, &this->sampler);
	}

	void		remove_sampler_memory()
	{
		if (this->sampler)
		{
			this->sampler->Release();
			this->sampler = NULL;
		}
	}

public:
	grng_sampler(const grng_sampler &s) = delete;
	grng_sampler(grng_sampler &&s) = delete;
	grng_sampler() : GRNG_BINDABLE()
	{
		this->set_sampler_memory();
	}

	~grng_sampler()
	{
		this->remove_sampler_memory();
	}


	void		bind() override
	{
		this->device_context->PSSetSamplers(0u, 1u, &this->sampler);
	}
};

using GRNG_SAMPLER = grng_sampler;
