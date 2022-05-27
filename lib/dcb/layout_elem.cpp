
#include "layout_elem.h"
#include <cassert>


pulsar::dcb::layout_elem	&pulsar::dcb::layout_elem::operator[](const std::string &key)
{
	assert(("Getting access to non-struct element is forbidden", this->m_type == pulsar::dcb::Struct));

	auto &extra_data = *this->m_extra_data;
	if (auto elem_it = extra_data.m_keys.find(key); elem_it != extra_data.m_keys.end())
		return (extra_data.m_elems[elem_it->second]);

	return (layout_elem::get_empty_elem());
}
const pulsar::dcb::layout_elem	&pulsar::dcb::layout_elem::operator[](const std::string &key) const
{
	return (const_cast<layout_elem&>(*this)[key]);
}

pulsar::dcb::layout_elem		&pulsar::dcb::layout_elem::add(pulsar::dcb::TYPE type, const std::string &key)
{
	this->add_data(type, key);
	return (*this);
}

bool	pulsar::dcb::layout_elem::exists() const
{
	return (this->m_type != pulsar::dcb::Empty);
}

pulsar::dcb::layout_elem::layout_elem(pulsar::dcb::TYPE type)
{
	assert(type != pulsar::dcb::Empty);

	this->m_type = type;
	if (this->m_type == pulsar::dcb::Struct)
		this->m_extra_data = std::make_shared<extra_data>();
}

pulsar::dcb::layout_elem	&pulsar::dcb::layout_elem::get_empty_elem()
{
	static layout_elem empty_elem;
	return (empty_elem);
}

void	pulsar::dcb::layout_elem::add_data(pulsar::dcb::TYPE type, const std::string &key)
{
	assert(("Adding to non-struct element is forbidden", this->m_type == pulsar::dcb::Struct));
	assert(("Invalid key name", this->validate_key(key)));

	auto &extra_data = *this->m_extra_data;
	assert(("Key already exists", (extra_data.m_keys.find(key) == extra_data.m_keys.end())));

	extra_data.m_elems.push_back(layout_elem(type));
	extra_data.m_keys[key] = extra_data.m_elems.size() - 1;
}

bool	pulsar::dcb::layout_elem::validate_key(const std::string &key)
{
	for (char c : key)
	{
		if (!std::isalnum(c) && c != '_')
			return (false);
	}

	return (!key.empty() && !std::isdigit(key.front()));
}
