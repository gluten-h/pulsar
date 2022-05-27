
#include "raw_layout.h"


pulsar::dcb::raw_layout::raw_layout() : pulsar::dcb::layout(std::shared_ptr<pulsar::dcb::layout_elem>(new pulsar::dcb::layout_elem(pulsar::dcb::Struct)))
{

}

pulsar::dcb::layout_elem	&pulsar::dcb::raw_layout::operator[](const std::string &key)
{
	return (*this->m_root)[key];
}


pulsar::dcb::layout_elem	&pulsar::dcb::raw_layout::add(pulsar::dcb::TYPE type, const std::string &key)
{
	return (this->m_root->add(type, key));
}

std::shared_ptr<pulsar::dcb::layout_elem>	pulsar::dcb::raw_layout::yield_finalize_root()
{
	std::shared_ptr<pulsar::dcb::layout_elem> root = std::move(this->m_root);
	root->finalize(0ull);
	*this = raw_layout();

	return (root);
}

std::shared_ptr<pulsar::dcb::layout_elem>	pulsar::dcb::raw_layout::share_finalize_root()
{
	std::shared_ptr<pulsar::dcb::layout_elem> root = this->m_root;
	root->finalize(0ull);

	return (root);
}
