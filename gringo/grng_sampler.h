#pragma once

#include "grng_bindable.h"


class grng_sampler : public GRNG_BINDABLE
{
private:
	ID3D11SamplerState		*sampler = NULL;
	UINT					slot = 0u;


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
	grng_sampler(UINT slot = 0u) : GRNG_BINDABLE()
	{
		this->type = GRNG_BINDABLE_TYPE::SAMPLER;

		this->set_sampler_memory();
		this->set_slot(slot);
	}

	~grng_sampler()
	{
		this->remove_sampler_memory();
	}

	void		set_slot(UINT slot)
	{
		this->slot = slot;
	}


	static GRNG_BINDABLE		*create_manager_ptr()
	{
		grng_sampler *s = new grng_sampler;

		return (s);
	}


	void		bind() override
	{
		this->device_context->PSSetSamplers(this->slot, 1u, &this->sampler);
	}

	void		destroy() override
	{
		this->remove_sampler_memory();
	}
};

using GRNG_SAMPLER = grng_sampler;
