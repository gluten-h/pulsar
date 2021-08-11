#pragma once

#include "grng_rg_source.h"
#include "grng_bindable.h"

#include <type_traits>


template<typename T>
class grng_rg_buffer_source : public GRNG_RG_SOURCE
{
private:
	static_assert(std::is_base_of_v<GRNG_BUFFER_RESOURCE, T>, "GRNG_RG_BUFFER_SOURCE target type must be a GRNG_BUFFER_RESOURCE type");

private:
	T		*buffer = NULL;
	bool	linked = false;

public:
	grng_rg_buffer_source(){ }
	grng_rg_buffer_source(const std::string &name, T *source_buffer = NULL) : GRNG_RG_SOURCE(name)
	{
		this->buffer = source_buffer;
	}

	GRNG_BUFFER_RESOURCE	*yield_buffer() override
	{
		if (this->linked)
			GRNG_THROW_RG_EXC("GRNG_RG_BUFFER_SOURCE " + this->get_name() + ": Source " + this->get_name() + " has already been linked");
		this->linked = true;

		return (this->buffer);
	}
};

template<typename T>
using GRNG_RG_BUFFER_SOURCE = grng_rg_buffer_source<T>;
