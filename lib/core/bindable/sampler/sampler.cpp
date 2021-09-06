
#include "sampler.h"


void		PULSAR::SAMPLER::copy_assign(const SAMPLER &s)
{
	this->sampler = s.sampler;
	this->slot = s.slot;
	if (this->sampler)
		this->sampler->AddRef();
}


PULSAR::SAMPLER		&PULSAR::SAMPLER::operator=(const SAMPLER &s)
{
	if (this->sampler != s.sampler)
		this->remove_sampler_memory();
	this->copy_assign(s);

	return (*this);
}

PULSAR::SAMPLER::SAMPLER(const SAMPLER &s) : PULSAR::BINDABLE()
{
	this->type = PULSAR::BINDABLE_TYPE::SAMPLER;
	this->copy_assign(s);
}

PULSAR::SAMPLER::SAMPLER(UINT slot) : PULSAR::BINDABLE()
{
	this->type = PULSAR::BINDABLE_TYPE::SAMPLER;

	this->set_sampler_memory();
	this->set_slot(slot);
}

PULSAR::SAMPLER::~SAMPLER()
{
	this->remove_sampler_memory();
}
