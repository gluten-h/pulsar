#pragma once

#include "grng_exc_macros.h"

#include <string>


class grng_rg_source
{
private:
	std::string		name;


	void		copy_assign(const grng_rg_source &s)
	{
		this->name = s.name;
	}

public:
	grng_rg_source		&operator=(const grng_rg_source &o)
	{
		this->copy_assign(o);

		return (*this);
	}
	grng_rg_source(const grng_rg_source &s)
	{
		this->copy_assign(s);
	}
	grng_rg_source(){ }
	grng_rg_source(const std::string &name)
	{
		this->name = name;
	}

	const std::string		&get_name() const
	{
		return (this->name);
	}


	virtual void		validate() const{ }


	virtual GRNG_BUFFER_RESOURCE		*yield_buffer()
	{
		GRNG_THROW_RG_EXC("GRNG_RG_SOURCE " + this->name + ": Source cannot be accessed as buffer");
	}

	virtual GRNG_BINDABLE				*yield_bindable()
	{
		GRNG_THROW_RG_EXC("GRNG_RG_SOURCE " + this->name + ": Source cannot be accessed as bindable");
	}
};

using GRNG_RG_SOURCE = grng_rg_source;
