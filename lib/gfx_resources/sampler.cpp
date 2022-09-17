
#include "sampler.h"
#include "exceptions/gfx_exception.h"


pulsar::sampler::sampler(UINT slot)
{
	this->set();
	this->m_slot = slot;
}

pulsar::sampler::sampler(D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE address_mode, UINT slot)
{
	this->create_sampler(filter, address_mode);
	this->m_slot = slot;
}

pulsar::sampler::~sampler()
{
	this->destroy_sampler();
}

void	pulsar::sampler::create_sampler(D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE address_mode)
{
	D3D11_SAMPLER_DESC sd;
	ZeroMemory(&sd, sizeof(D3D11_SAMPLER_DESC));

	sd.Filter = filter;
	sd.AddressU = address_mode;
	sd.AddressV = address_mode;
	sd.AddressW = address_mode;

	GFX_ASSERT(pulsar::gfx::instance().device()->CreateSamplerState(&sd, &this->mp_sampler));
}

void	pulsar::sampler::destroy_sampler()
{
	if (this->mp_sampler)
	{
		this->mp_sampler->Release();
		this->mp_sampler = NULL;
	}
}

void	pulsar::sampler::set(D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE address_mode)
{
	this->destroy_sampler();
	this->create_sampler(filter, address_mode);
}

void	pulsar::sampler::set_slot(UINT slot)
{
	this->m_slot = slot;
}

void	pulsar::sampler::bind() const
{
	pulsar::gfx::instance().device_context()->PSSetSamplers(this->m_slot, 1u, &this->mp_sampler);
}

void	pulsar::sampler::unbind() const
{
	ID3D11SamplerState *null[1] = { NULL };
	pulsar::gfx::instance().device_context()->PSSetSamplers(this->m_slot, 1u, null);
}
