
#include "buffer.h"
#include "raw_layout.h"
#include "baked_layout.h"


void	PULSAR::dcb::buffer::set_layout(PULSAR::dcb::raw_layout &&raw_layout)
{
	this->set_layout(PULSAR::dcb::baked_layout(std::move(raw_layout)));
}

void	PULSAR::dcb::buffer::set_layout(PULSAR::dcb::baked_layout &&baked_layout)
{
	this->m_data.resize(baked_layout.size(), 0);
	this->mp_root = baked_layout.yield_root();
}

void	PULSAR::dcb::buffer::set_layout(PULSAR::dcb::raw_layout &raw_layout)
{
	this->set_layout(PULSAR::dcb::baked_layout(raw_layout));
}

void	PULSAR::dcb::buffer::set_layout(const PULSAR::dcb::baked_layout &baked_layout)
{
	this->m_data.resize(baked_layout.size(), 0);
	this->mp_root = baked_layout.share_root();
}

const char	*PULSAR::dcb::buffer::data() const noexcept
{
	return (this->m_data.data());
}

size_t	PULSAR::dcb::buffer::size() const noexcept
{
	return (this->m_data.size());
}

bool	PULSAR::dcb::buffer::is_modified() const noexcept
{
	return (this->m_is_modified);
}

void	PULSAR::dcb::buffer::set_updated()
{
	this->m_is_modified = false;
}
