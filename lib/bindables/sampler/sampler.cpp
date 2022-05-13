
#include "sampler.h"


PULSAR::sampler::sampler()
{

}

PULSAR::sampler::sampler(UINT slot)
{
	this->create_sampler();
	this->set_slot(slot);
}

PULSAR::sampler::~sampler()
{
	this->free();
}

void	PULSAR::sampler::bind() const
{
	PULSAR::gfx::get().device_context()->PSSetSamplers(this->m_slot, 1u, &this->mp_sampler);
}

void	PULSAR::sampler::unbind() const
{
	ID3D11SamplerState *null_ptr[1] = { NULL };
	PULSAR::gfx::get().device_context()->PSSetSamplers(this->m_slot, 1u, null_ptr);
}
