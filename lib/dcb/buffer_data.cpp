
#include "buffer.h"
#include "raw_layout.h"
#include "baked_layout.h"


void	pulsar::dcb::buffer::set_layout(pulsar::dcb::raw_layout &&raw_layout)
{
	this->set_layout(pulsar::dcb::baked_layout(std::move(raw_layout)));
}

void	pulsar::dcb::buffer::set_layout(pulsar::dcb::baked_layout &&baked_layout)
{
	this->m_data.resize(baked_layout.size(), 0);
	this->mp_root = baked_layout.yield_root();
}

void	pulsar::dcb::buffer::set_layout(pulsar::dcb::raw_layout &raw_layout)
{
	this->set_layout(pulsar::dcb::baked_layout(raw_layout));
}

void	pulsar::dcb::buffer::set_layout(const pulsar::dcb::baked_layout &baked_layout)
{
	this->m_data.resize(baked_layout.size(), 0);
	this->mp_root = baked_layout.share_root();
}

const char	*pulsar::dcb::buffer::data() const noexcept
{
	return (this->m_data.data());
}

size_t	pulsar::dcb::buffer::size() const noexcept
{
	return (this->m_data.size());
}

bool	pulsar::dcb::buffer::is_modified() const noexcept
{
	return (this->m_is_modified);
}

void	pulsar::dcb::buffer::set_updated()
{
	this->m_is_modified = false;
}
