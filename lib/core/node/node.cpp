
#include "node/node.h"


void	PULSAR::node::destroy()
{
	this->mp_scene->m_registry.destroy(this->m_id);
}

bool	PULSAR::node::is_valid() const
{
	return (this->m_id != PULSAR::ecs::INVALID_ENTITY);
}

PULSAR::node::operator bool() const
{
	return (this->is_valid());
}
