#pragma once

#include "grng_bindable.h"
#include "grng_bindable_entity.h"


class grng_sampler : public GRNG_BINDABLE
{
private:
	ID3D11SamplerState		*sampler = NULL;
	UINT					slot = 0u;


	void					set_sampler_memory();
	void					remove_sampler_memory();

	void					copy_assign(const grng_sampler &s);

protected:
	void		remove_from_entities() override
	{
		for (auto &it : this->entities)
			it->_remove_bindable_ignore_entity(this);
		this->entities.clear();
	}

public:
	using GRNG_BINDABLE::bind;

public:
	grng_sampler			&operator=(const grng_sampler &s);
	grng_sampler(const grng_sampler &s);
	grng_sampler(UINT slot = 0u);
	~grng_sampler();

	void					set_slot(UINT slot);

	static grng_sampler		*create();

	void		bind() const override
	{
		this->device_context->PSSetSamplers(this->slot, 1u, &this->sampler);
		GRNG_BINDABLE::add_unbind(*this);
	}

	void		unbind() const override
	{
		this->device_context->PSGetSamplers(this->slot, 0u, NULL);
	}
};

using GRNG_SAMPLER = grng_sampler;
