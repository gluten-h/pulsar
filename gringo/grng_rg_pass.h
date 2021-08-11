#pragma once

#include "grng_exc_macros.h"

#include "grng_rg_input.h"
#include "grng_rg_source.h"

#include "grng_utils.h"

#include <string>
#include <unordered_map>
#include <stdexcept>


enum class GRNG_RG_COMPONENT_TYPE
{
	NONE,
	INPUT,
	SOURCE,
	PASS
};


class grng_rg_pass
{
private:
	std::string		name;

	int		dependency_level = -1;
	bool	_linked = false;

	std::unordered_map<std::string, GRNG_RG_INPUT*>		inputs;
	std::unordered_map<std::string, GRNG_RG_SOURCE*>	sources;


	void		copy_assign(const grng_rg_pass &p)
	{
		this->name = p.name;
		this->inputs = p.inputs;
		this->sources = p.sources;
	}

public:
	grng_rg_pass		&operator=(const grng_rg_pass &p)
	{
		this->copy_assign(p);

		return (*this);
	}
	grng_rg_pass(const grng_rg_pass &p)
	{
		this->copy_assign(p);
	}
	grng_rg_pass(){ }
	grng_rg_pass(const std::string &name)
	{
		this->name = name;
	}

	void			register_input(const GRNG_RG_INPUT &input)
	{
		const std::string input_name = input.get_name();
		try
		{
			this->inputs.at(input_name);
			GRNG_THROW_RG_EXC("GRNG_RG_PASS " + this->name + ": Input " + input_name + " already exists");

			return;
		}
		catch (const std::out_of_range &ex){ }

		this->inputs[input_name] = (GRNG_RG_INPUT*)&input;
	}
	void			register_source(const GRNG_RG_SOURCE &source)
	{
		const std::string source_name = source.get_name();
		try
		{
			this->sources.at(source_name);
			GRNG_THROW_RG_EXC("GRNG_RG_PASS " + this->name + ": Source " + source_name + " already exists");

			return;
		}
		catch (const std::out_of_range &ex){ }

		this->sources[source_name] = (GRNG_RG_SOURCE*)&source;
	}

	void			set_dependency_level(unsigned int dependency_level)
	{
		this->dependency_level = dependency_level;
	}
	int				get_dependency_level() const
	{
		return (this->dependency_level);
	}

	void			set_linked()
	{
		this->_linked = true;
	}
	bool			linked() const
	{
		return (this->_linked);
	}

	GRNG_RG_INPUT	&get_input(const std::string &name)
	{
		try
		{
			return (*this->inputs.at(name));
		}
		catch (const std::out_of_range &ex)
		{
			GRNG_THROW_RG_EXC("GRNG_RG_PASS " + this->name + ": Input " + name + " not found");
		}
	}
	GRNG_RG_SOURCE	&get_source(const std::string &name)
	{
		try
		{
			return (*this->sources.at(name));
		}
		catch (const std::out_of_range &ex)
		{
			GRNG_THROW_RG_EXC("GRNG_RG_PASS " + this->name +  ": Source " + name + " not found");
		}
	}

	std::string		get_name() const
	{
		return (this->name);
	}
	const std::unordered_map<std::string, GRNG_RG_INPUT*>	get_inputs() const
	{
		return (this->inputs);
	}


	void			set_input_linkage(const std::string &input_name, const std::string source)
	{
		GRNG_RG_INPUT &input = this->get_input(input_name);
		std::vector<std::string> source_split = GRNG_UTILS::str_split(source, '.');
		if (source_split.size() != 2u)
			GRNG_THROW_RG_EXC("GRNG_RG_PASS " + this->name + ": Input source has invalid format");

		input.set_source(source_split[0], source_split[1]);
	}


	virtual void		validate() const
	{
		for (auto &i : this->inputs)
			i.second->validate();
		for (auto &s : this->sources)
			s.second->validate();
	}

	virtual void	execute() = 0;
};

using GRNG_RG_PASS = grng_rg_pass;
