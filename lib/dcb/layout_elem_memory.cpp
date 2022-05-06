
#include "layout_elem.h"
#include <cassert>


bool	PULSAR::dcb::layout_elem::crosses_boundary(size_t offset, size_t size) const noexcept
{
	size_t end = offset + size;
	size_t b_start = offset / 16ull;
	size_t b_end = end / 16ull;

	return (size > 16ull || (b_start != b_end && end % 16ull != 0ull));
}

size_t	PULSAR::dcb::layout_elem::pad_boundary(size_t offset) const noexcept
{
	return (offset + (16ull - offset % 16ull) % 16ull);
}

size_t	PULSAR::dcb::layout_elem::pad_if_crosses_boundary(size_t offset, size_t size) const noexcept
{
	if (this->crosses_boundary(offset, size))
		return (this->pad_boundary(offset));
	return (offset);
}


// OFFSET BASED, FUNCTIONS WORK ONLY AFTER FINALIZATION
size_t	PULSAR::dcb::layout_elem::get_offset_begin() const noexcept
{
	return (this->m_offset);
}

size_t	PULSAR::dcb::layout_elem::get_offset_end() const noexcept
{
	switch (this->m_type)
	{
#define DCB_RDT_MACRO(t)																	\
					case t:																	\
					{																		\
						return (this->m_offset + PULSAR::dcb::type_attr<t>::hlsl_size);		\
					}
		DCB_RAW_DATA_TYPES
#undef DCB_RDT_MACRO
		case PULSAR::dcb::Struct:
		{
			return (this->pad_boundary(this->m_extra_data->m_elems.back().get_offset_end()));
		}
	}
}

size_t	PULSAR::dcb::layout_elem::size() const noexcept
{
	return (this->get_offset_end() - this->get_offset_begin());
}

size_t	PULSAR::dcb::layout_elem::finalize(size_t offset_in)
{
	switch (this->m_type)
	{
#define DCB_RDT_MACRO(t)																									\
					case t:																									\
					{																										\
						this->m_offset = this->pad_if_crosses_boundary(offset_in, PULSAR::dcb::type_attr<t>::hlsl_size);	\
						return (this->m_offset + type_attr<t>::hlsl_size);													\
					}
		DCB_RAW_DATA_TYPES
#undef DCB_RDT_MACRO
		case PULSAR::dcb::Struct:
		{
			return (this->finalize_struct(offset_in));
		}
		default:
		{
			assert(("Invalid dcb type", false));
			break;
		}
	}
}

size_t	PULSAR::dcb::layout_elem::finalize_struct(size_t offset_in)
{
	assert(("Empty struct is not allowed", this->m_extra_data->m_elems.size() > 0ull));

	auto &extra_data = *this->m_extra_data;
	this->m_offset = this->pad_boundary(offset_in);

	size_t offset = this->m_offset;
	for (auto &elem : extra_data.m_elems)
		offset = elem.finalize(offset);

	return (offset);
}
