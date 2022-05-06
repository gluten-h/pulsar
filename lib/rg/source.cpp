
#include "source.h"
#include "exceptions/rg_exception.h"


PULSAR::rg::source::source(const std::string &name)
{
	this->m_name = name;
}

const std::string	&PULSAR::rg::source::name() const
{
	return (this->m_name);
}

PULSAR::bindable	**PULSAR::rg::source::yield_bindable()
{
	THROW_RG_EXC("Source " + this->m_name + " cannot be accessed as a bindable");
	return (NULL);
}

PULSAR::buffer_resource		**PULSAR::rg::source::yield_buffer_resource()
{
	THROW_RG_EXC("Source " + this->m_name + " cannot be accessed as a buffer resource");
	return (NULL);
}

void	PULSAR::rg::source::validate() const
{

}
