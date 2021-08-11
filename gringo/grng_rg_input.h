#pragma once

#include "grng_rg_component.h"
#include "grng_exc_macros.h"
#include "grng_rg_source.h"

#include <string>


class grng_rg_input : public GRNG_RG_COMPONENT
{
private:
	std::string		name;
	std::string		source_pass_name;
	std::string		source_name;


	void		copy_assign(const grng_rg_input &i)
	{
		this->name = i.name;
		this->source_pass_name = i.source_pass_name;
		this->source_name = i.source_name;
	}

public:
	grng_rg_input		&operator=(const grng_rg_input &i)
	{
		this->copy_assign(i);

		return (*this);
	}
	grng_rg_input(const grng_rg_input &i) : GRNG_RG_COMPONENT()
	{
		this->type = GRNG_RG_COMPONENT_TYPE::INPUT;
		this->copy_assign(i);
	}
	grng_rg_input() : GRNG_RG_COMPONENT()
	{
		this->type = GRNG_RG_COMPONENT_TYPE::INPUT;
	}
	grng_rg_input(const std::string &name) : GRNG_RG_COMPONENT()
	{
		this->type = GRNG_RG_COMPONENT_TYPE::INPUT;
		this->name = name;
	}

	const std::string		&get_name() const
	{
		return (this->name);
	}
	const std::string		&get_source_pass_name() const
	{
		return (this->source_pass_name);
	}
	const std::string		&get_source_name() const
	{
		return (this->source_name);
	}

	void		set_source(const std::string &source_pass_name, const std::string &source_name)
	{
		if (source_pass_name.empty())
			GRNG_THROW_RG_EXC("GRNG_RG_INPUT " + this->name + ": Empty source name");
		this->source_pass_name = source_pass_name;

		if (source_name.empty())
			GRNG_THROW_RG_EXC("GRNG_RG_INPUT " + this->name + ": Empty source name");
		this->source_name = source_name;
	}


	virtual void		validate() const{ }
	virtual void		bind(GRNG_RG_SOURCE *source) = 0;
};

using GRNG_RG_INPUT = grng_rg_input;
