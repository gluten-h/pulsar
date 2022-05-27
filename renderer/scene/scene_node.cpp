
#include "scene.h"
#include "node/node.h"
#include "transform/transform_component.h"


pulsar::node	pulsar::scene::create_node()
{
	pulsar::node node(this->m_registry.create(), this);
	node.add_component<pulsar::transform_component>();

	return (node);
}
