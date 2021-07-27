#pragma once

#include <string>


class grng_rg_output
{
private:
	std::string		name;


	void		copy_assign(const grng_rg_output &o)
	{
		this->name = o.name;
	}

public:
	grng_rg_output		&operator=(const grng_rg_output &o)
	{
		this->copy_assign(o);

		return (*this);
	}
	grng_rg_output(const grng_rg_output &o)
	{
		this->copy_assign(o);
	}
	grng_rg_output(const std::string &name)
	{
		this->name = name;
	}

	const std::string		&get_name() const
	{
		return (this->name);
	}
};

using GRNG_RG_OUTPUT = grng_rg_output;
