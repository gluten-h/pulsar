#pragma once

#include "grng_rg_source.h"
#include "grng_bindable.h"

#include <type_traits>


template<typename T>
class grng_rg_bindable_source : public GRNG_RG_SOURCE
{
private:
	static_assert(std::is_base_of_v<GRNG_BINDABLE, T>, "GRNG_RG_BINDABLE_SOURCE target type must be a GRNG_BINDABLE type");

private:
	T		*bindable = NULL;

public:
	grng_rg_bindable_source(){ }
	grng_rg_bindable_source(const std::string &name, T *source_bindable = NULL) : GRNG_RG_SOURCE(name)
	{
		this->bindable = source_bindable;
	}

	GRNG_BINDABLE		*yield_bindable() override
	{
		return (this->bindable);
	}
};

template<typename T>
using GRNG_RG_BINDABLE_SOURCE = grng_rg_bindable_source<T>;
