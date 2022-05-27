
#include "input.h"
#include "exceptions/rg_exception.h"


pulsar::rg::input::input(const std::string & name)
{
	this->m_name = name;
}

const std::string	&pulsar::rg::input::name() const
{
	return (this->m_name);
}

const std::string	&pulsar::rg::input::source_name() const
{
	return (this->m_source_name);
}

const std::string	&pulsar::rg::input::source_pass_name() const
{
	return (this->m_source_pass_name);
}

void	pulsar::rg::input::set_source(const std::string &source_pass_name, const std::string &source_name)
{
	if (source_pass_name.empty())
		THROW_RG_EXC("Empty source pass name");
	if (source_name.empty())
		THROW_RG_EXC("Empry source name");

	this->m_source_name = source_name;
	this->m_source_pass_name = source_pass_name;
}

void	pulsar::rg::input::validate() const
{

}
