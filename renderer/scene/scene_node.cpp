
#include "scene.h"
#include "node/node.h"
#include "metadata/metadata_component.h"
#include "transform/transform_component.h"


pulsar::node	pulsar::scene::create_node(const char *name)
{
	pulsar::node node(this->m_registry.create(), this);

	node.add_component<pulsar::metadata_component>(name);
	node.add_component<pulsar::transform_component>();

	return (node);
}
