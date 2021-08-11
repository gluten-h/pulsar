#pragma once

#include "grng_rg_input.h"
#include "grng_bindable.h"

#include <type_traits>


template<typename T>
class grng_rg_buffer_input : public GRNG_RG_INPUT
{
private:
	static_assert(std::is_base_of_v<GRNG_BUFFER_RESOURCE, T>, "GRNG_RG_BUFFER_INPUT target type must be a GRNG_BUFFER_RESOURCE type");

private:
	T			*source_buffer = NULL;

public:
	grng_rg_buffer_input(){ }
	grng_rg_buffer_input(const std::string &name/*, T *source = NULL*/) : GRNG_RG_INPUT(name)
	{
		//this->source_buffer = source;
	}

	void		validate() const override
	{
		if (!this->source_buffer)
			GRNG_THROW_RG_EXC("GRNG_RG_BUFFER_INPUT " + this->get_name() + ": Unlinked input " + this->get_name());
	}

	void		bind(GRNG_RG_SOURCE *source) override
	{
		T *source_buffer = dynamic_cast<T*>(source->yield_buffer());
		if (!source_buffer)
		{
			GRNG_THROW_RG_EXC("GRNG_RG_BUFFER_INPUT " + this->get_name() + ": Input " + this->get_name() + "of type " + typeid(T).name() + "is no compatible with "
							  + this->get_source_pass_name() + "." + this->get_source_name() + " of type " + typeid(*source->get_buffer()).name());
		}
		this->source_buffer = source_buffer;
	}
};

template<typename T>
using GRNG_RG_BUFFER_INPUT = grng_rg_buffer_input<T>;
