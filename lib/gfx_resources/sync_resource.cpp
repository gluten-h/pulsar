
#include "sync_resource.h"


void	pulsar::sync_resource::link(sync_resource *resource)
{
	this->m_linked_resources.push_back(resource);
}

void	pulsar::sync_resource::unlink(sync_resource *resource)
{
	auto it = std::find(this->m_linked_resources.begin(), this->m_linked_resources.end(), resource);
	if (it != this->m_linked_resources.end())
		this->m_linked_resources.erase(it);
}

void	pulsar::sync_resource::resize_linked(UINT width, UINT height)
{
	for (pulsar::sync_resource *res : this->m_linked_resources)
		res->resize(width, height);
}
