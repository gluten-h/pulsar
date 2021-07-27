#pragma once

#include <string>


class grng_rg_input
{
private:
	std::string		name;


	void		copy_assign(const grng_rg_input &i)
	{
		this->name = i.name;
	}

public:
	grng_rg_input		&operator=(const grng_rg_input &i)
	{
		this->copy_assign(i);

		return (*this);
	}
	grng_rg_input(const grng_rg_input &i)
	{
		this->copy_assign(i);
	}
	grng_rg_input(const std::string &name)
	{
		this->name = name;
	}

	const std::string		&get_name() const
	{
		return (this->name);
	}
};

using GRNG_RG_INPUT = grng_rg_input;
