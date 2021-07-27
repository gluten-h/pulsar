#pragma once

#include "grng_rg_input.h"
#include "grng_rg_output.h"

#include <string>
#include <unordered_map>
#include <stdexcept>


enum class GRNG_RG_COMPONENT_TYPE
{
	NONE,
	INPUT,
	OUTPUT,
	PASS
};


class grng_pass
{
private:
	std::string		name;

	std::unordered_map<std::string, GRNG_RG_INPUT>		inputs;
	std::unordered_map<std::string, GRNG_RG_OUTPUT>		outputs;


	void		copy_assign(const grng_pass &p)
	{
		this->name = p.name;
		this->inputs = p.inputs;
		this->outputs = p.outputs;
	}

public:
	grng_pass		&operator=(const grng_pass &p)
	{
		this->copy_assign(p);

		return (*this);
	}
	grng_pass(const grng_pass &p)
	{
		this->copy_assign(p);
	}
	grng_pass(std::string &name)
	{
		this->name = name;
	}

	void			add_input(const GRNG_RG_INPUT &input)
	{
		const std::string input_name = input.get_name();
		try
		{
			this->inputs.at(input_name);
			return;
		}
		catch (const std::out_of_range &ex)
		{
			this->inputs[input_name] = input;
		}
	}
	void			add_output(const GRNG_RG_OUTPUT &output)
	{
		const std::string output_name = output.get_name();
		try
		{
			this->outputs.at(output_name);
			return;
		}
		catch (const std::out_of_range &ex)
		{
			this->outputs[output_name] = output;
		}
	}

	//GRNG_RG_INPUT	&get_input(const std::string &name)
	//{
	//	try
	//	{
	//
	//	}
	//	catch (const std::out_of_range &ex)
	//	{
	//
	//	}
	//}

	virtual void	execute() = 0;
};

using GRNG_PASS = grng_pass;
