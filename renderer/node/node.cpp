
#include "node/node.h"


pulsar::node::node(pulsar::ecs::entity id, pulsar::scene *scene)
{
	this->m_id = id;
	this->mp_scene = scene;
}

void	pulsar::node::destroy()
{
	this->mp_scene->m_registry.destroy(this->m_id);
}

bool	pulsar::node::is_valid() const
{
	return (this->m_id != pulsar::ecs::null);
}

pulsar::node::operator bool() const
{
	return (this->is_valid());
}
