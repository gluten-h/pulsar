
#include "baked_layout.h"


pulsar::dcb::baked_layout::baked_layout(pulsar::dcb::raw_layout &&raw_layout) : pulsar::dcb::layout(raw_layout.yield_finalize_root())
{

}

pulsar::dcb::baked_layout::baked_layout(pulsar::dcb::raw_layout &raw_layout) : pulsar::dcb::layout(raw_layout.share_finalize_root())
{

}

const pulsar::dcb::layout_elem	&pulsar::dcb::baked_layout::operator[](const std::string &key) const
{
	return const_cast<const layout_elem&>(*this->m_root)[key];
}

std::shared_ptr<pulsar::dcb::layout_elem>	pulsar::dcb::baked_layout::yield_root()
{
	return (std::move(this->m_root));
}

std::shared_ptr<pulsar::dcb::layout_elem>	pulsar::dcb::baked_layout::share_root() const
{
	return (this->m_root);
}

size_t	pulsar::dcb::baked_layout::size() const noexcept
{
	return (this->m_root->size());
}
