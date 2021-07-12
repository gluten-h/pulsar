#pragma once

#include "grng_bindable.h"


class grng_sampler : public GRNG_BINDABLE
{
private:
	ID3D11SamplerState		*sampler = NULL;
	UINT					slot = 0u;


	void					set_sampler_memory();
	void					remove_sampler_memory();

	void					copy_assign(const grng_sampler &s);

public:
	grng_sampler			&operator=(const grng_sampler &s);
	grng_sampler(const grng_sampler &s);
	grng_sampler(UINT slot = 0u);
	~grng_sampler();

	void					set_slot(UINT slot);

	static GRNG_BINDABLE	*create_manager_ptr();


	void		bind() const override
	{
		this->device_context->PSSetSamplers(this->slot, 1u, &this->sampler);
	}
};

using GRNG_SAMPLER = grng_sampler;
