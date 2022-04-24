
#include "scene.h"
#include "node/node.h"


PULSAR::node	PULSAR::scene::create_node()
{
	PULSAR::node node(this->m_registry.create(), this);
	node.add_component<PULSAR::transform_component>();

	return (node);
}
