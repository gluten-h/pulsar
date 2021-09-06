
#include "sampler.h"


void		PULSAR::SAMPLER::set_sampler_memory()
{
	HRESULT hr;

	D3D11_SAMPLER_DESC sd;
	ZeroMemory(&sd, sizeof(D3D11_SAMPLER_DESC));
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	GFX_ASSERT(this->device->CreateSamplerState(&sd, &this->sampler));
}

void		PULSAR::SAMPLER::remove_sampler_memory()
{
	if (this->sampler)
	{
		ULONG ref_count = this->sampler->Release();
		if (ref_count == 0)
			this->sampler = NULL;
	}
}

void		PULSAR::SAMPLER::set_slot(UINT slot)
{
	this->slot = slot;
}


PULSAR::SAMPLER		*PULSAR::SAMPLER::create()
{
	return ((PULSAR::SAMPLER*)PULSAR::BINDABLE::add_to_manager(new PULSAR::SAMPLER));
}
