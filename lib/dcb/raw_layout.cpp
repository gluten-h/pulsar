
#include "raw_layout.h"


PULSAR::dcb::raw_layout::raw_layout() : PULSAR::dcb::layout(std::shared_ptr<PULSAR::dcb::layout_elem>(new PULSAR::dcb::layout_elem(PULSAR::dcb::Struct)))
{

}

PULSAR::dcb::layout_elem	&PULSAR::dcb::raw_layout::operator[](const std::string &key)
{
	return (*this->m_root)[key];
}


PULSAR::dcb::layout_elem	&PULSAR::dcb::raw_layout::add(PULSAR::dcb::TYPE type, const std::string &key)
{
	return (this->m_root->add(type, key));
}

std::shared_ptr<PULSAR::dcb::layout_elem>	PULSAR::dcb::raw_layout::yield_finalize_root()
{
	std::shared_ptr<PULSAR::dcb::layout_elem> root = std::move(this->m_root);
	root->finalize(0ull);
	*this = raw_layout();

	return (root);
}

std::shared_ptr<PULSAR::dcb::layout_elem>	PULSAR::dcb::raw_layout::share_finalize_root()
{
	std::shared_ptr<PULSAR::dcb::layout_elem> root = this->m_root;
	root->finalize(0ull);

	return (root);
}
