
#include "script_system.h"
#include "script/script_component.h"


pulsar::script_system::script_system(pulsar::ecs::registry *registry) : pulsar::ecs::system(registry)
{

}

void	pulsar::script_system::execute(float delta_time)
{
	auto view = this->mp_registry->view<pulsar::script_component>();

	for (auto entity : view)
	{
		pulsar::script *script = this->mp_registry->get<pulsar::script_component>(entity).script;
		script->execute(delta_time);
	}
}
