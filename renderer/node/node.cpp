
#include "node/node.h"


PULSAR::node::node(PULSAR::ecs::entity id, PULSAR::scene *p_scene)
{
	this->m_id = id;
	this->mp_scene = p_scene;
}

void	PULSAR::node::destroy()
{
	this->mp_scene->m_registry.destroy(this->m_id);
}

bool	PULSAR::node::is_valid() const
{
	return (this->m_id != PULSAR::ecs::null);
}

PULSAR::node::operator bool() const
{
	return (this->is_valid());
}
