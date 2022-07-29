
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

void	**pulsar::rg::source::get_async_data()
{
	THROW_RG_EXC("Invalid source: " + this->m_name);
	return (NULL);
}

pulsar::sync_resource	**pulsar::rg::source::yield_sync_data()
{
	THROW_RG_EXC("Invalid source: " + this->m_name);
	return (NULL);
}

void	pulsar::rg::source::validate() const
{

}
