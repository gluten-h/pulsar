
#include "buffer.h"
#include "raw_layout.h"
#include "baked_layout.h"
#include "layout_elem_ref.h"


pulsar::dcb::buffer::buffer(pulsar::dcb::raw_layout &&raw_layout) : buffer(pulsar::dcb::baked_layout(std::move(raw_layout)))
{

}

pulsar::dcb::buffer::buffer(pulsar::dcb::baked_layout &&baked_layout)
{
	this->set_layout(std::move(baked_layout));
}

pulsar::dcb::buffer::buffer(pulsar::dcb::raw_layout &raw_layout) : buffer(pulsar::dcb::baked_layout(raw_layout))
{

}

pulsar::dcb::buffer::buffer(const pulsar::dcb::baked_layout &baked_layout)
{
	this->set_layout(baked_layout);
}

pulsar::dcb::layout_elem_ref	pulsar::dcb::buffer::operator[](const std::string &key)
{
	return (pulsar::dcb::layout_elem_ref(&(*this->mp_root)[key], this->m_data.data(), &this->m_is_modified));
}
