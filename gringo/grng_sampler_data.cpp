
#include "grng_sampler.h"


void				grng_sampler::set_sampler_memory()
{
	HRESULT hr;

	D3D11_SAMPLER_DESC sd;
	ZeroMemory(&sd, sizeof(D3D11_SAMPLER_DESC));
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	GRNG_GFX_ASSERT(this->device->CreateSamplerState(&sd, &this->sampler));
}

void				grng_sampler::remove_sampler_memory()
{
	if (this->sampler)
	{
		ULONG ref_count = this->sampler->Release();
		if (ref_count == 0)
			this->sampler = NULL;
	}
}

void				grng_sampler::set_slot(UINT slot)
{
	this->slot = slot;
}

GRNG_BINDABLE		*grng_sampler::create_manager_ptr()
{
	grng_sampler *s = new grng_sampler;

	return (s);
}
