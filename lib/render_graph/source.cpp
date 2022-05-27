
#include "source.h"
#include "exceptions/rg_exception.h"


pulsar::rg::source::source(const std::string &name)
{
	this->m_name = name;
}

const std::string	&pulsar::rg::source::name() const
{
	return (this->m_name);
}

pulsar::bindable	**pulsar::rg::source::yield_bindable()
{
	THROW_RG_EXC("Source " + this->m_name + " cannot be accessed as a bindable");
	return (NULL);
}

pulsar::buffer_resource		**pulsar::rg::source::yield_buffer_resource()
{
	THROW_RG_EXC("Source " + this->m_name + " cannot be accessed as a buffer resource");
	return (NULL);
}

void	pulsar::rg::source::validate() const
{

}
