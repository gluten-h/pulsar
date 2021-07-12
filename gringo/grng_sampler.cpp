
#include "grng_sampler.h"


void				grng_sampler::copy_assign(const grng_sampler &s)
{
	this->sampler = s.sampler;
	this->slot = s.slot;
	if (this->sampler)
		this->sampler->AddRef();
}


grng_sampler		&grng_sampler::operator=(const grng_sampler &s)
{
	if (this->sampler != s.sampler)
		this->remove_sampler_memory();
	this->copy_assign(s);

	return (*this);
}

grng_sampler::grng_sampler(const grng_sampler &s) : GRNG_BINDABLE()
{
	this->type = GRNG_BINDABLE_TYPE::SAMPLER;
	this->copy_assign(s);
}

grng_sampler::grng_sampler(UINT slot) : GRNG_BINDABLE()
{
	this->type = GRNG_BINDABLE_TYPE::SAMPLER;

	this->set_sampler_memory();
	this->set_slot(slot);
}

grng_sampler::~grng_sampler()
{
	this->remove_sampler_memory();
}
