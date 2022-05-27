
#include "sampler.h"
#include "exceptions/gfx_exception.h"


void	pulsar::sampler::create_sampler()
{
	HRESULT hr;

	D3D11_SAMPLER_DESC sd;
	ZeroMemory(&sd, sizeof(D3D11_SAMPLER_DESC));
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	GFX_ASSERT(pulsar::gfx::instance().device()->CreateSamplerState(&sd, &this->mp_sampler));
}

void	pulsar::sampler::free()
{
	if (this->mp_sampler)
	{
		this->mp_sampler->Release();
		this->mp_sampler = NULL;
	}
}

void	pulsar::sampler::set_slot(UINT slot)
{
	this->m_slot = slot;
}
