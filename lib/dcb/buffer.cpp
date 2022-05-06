
#include "buffer.h"
#include "layout_elem_ref.h"
#include "baked_layout.h"


PULSAR::dcb::buffer::buffer(PULSAR::dcb::raw_layout &&raw_layout) : buffer(PULSAR::dcb::baked_layout(std::move(raw_layout)))
{

}

PULSAR::dcb::buffer::buffer(PULSAR::dcb::baked_layout &&baked_layout)
{
	this->set_layout(std::move(baked_layout));
}

PULSAR::dcb::buffer::buffer(PULSAR::dcb::raw_layout &raw_layout) : buffer(PULSAR::dcb::baked_layout(raw_layout))
{

}

PULSAR::dcb::buffer::buffer(const PULSAR::dcb::baked_layout &baked_layout)
{
	this->set_layout(baked_layout);
}

PULSAR::dcb::layout_elem_ref	PULSAR::dcb::buffer::operator[](const std::string &key)
{
	return (PULSAR::dcb::layout_elem_ref(&(*this->mp_root)[key], this->m_data.data(), &this->m_is_modified));
}
