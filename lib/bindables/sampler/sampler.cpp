
#include "sampler.h"


pulsar::sampler::sampler()
{
	this->m_slot = 0u;
}

pulsar::sampler::sampler(UINT slot)
{
	this->create_sampler();
	this->set_slot(slot);
}

pulsar::sampler::~sampler()
{
	this->free();
}

void	pulsar::sampler::bind() const
{
	pulsar::gfx::instance().device_context()->PSSetSamplers(this->m_slot, 1u, &this->mp_sampler);
}

void	pulsar::sampler::unbind() const
{
	ID3D11SamplerState *null_ptr[1] = { NULL };
	pulsar::gfx::instance().device_context()->PSSetSamplers(this->m_slot, 1u, null_ptr);
}
