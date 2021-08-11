#pragma once

#include "grng_rg_input.h"
#include "grng_bindable.h"

#include <type_traits>


template<typename T>
class grng_rg_bindable_input : public GRNG_RG_INPUT
{
private:
	static_assert(std::is_base_of_v<GRNG_BINDABLE, T>, "GRNG_RG_BINDABLE_INPUT target type must be a GRNG_BINDABLE type");

private:
	T		*source_bindable = NULL;

public:
	grng_rg_bindable_input(){ }
	grng_rg_bindable_input(const std::string &name/*, T *source = NULL*/) : GRNG_RG_INPUT(name)
	{
		//this->source_buffer = source;
	}

	void		validate() const override
	{
		if (!this->source_buffer)
			GRNG_THROW_RG_EXC("GRNG_RG_BINDABLE_INPUT " + this->get_name() + ": Unlinked input " + this->get_name());
	}

	void		bind(GRNG_RG_SOURCE *source) override
	{
		T *source_bindable = dynamic_cast<T*>(source->yield_bindable());
		if (!source_bindable)
		{
			GRNG_THROW_RG_EXC("GRNG_RG_BINDABLE_INPUT " + this->get_name() + ": Input " + this->get_name() + "of type " + typeid(T).name() + "is no compatible with "
							  + this->get_source_pass_name() + "." + this->get_source_name() + " of type " + typeid(*source->get_buffer()).name());
		}
		this->source_bindable = source_bindable;
	}
};

template<typename T>
using GRNG_RG_BINDABLE_INPUT = grng_rg_bindable_input<T>;
