
#include "script_system.h"
#include "script/script_component.h"


void	pulsar::script_system::execute(pulsar::ecs::registry &registry, float delta_time)
{
	auto view = registry.view<pulsar::script_component>();

	for (auto entity : view)
	{
		pulsar::script *script = view.get<pulsar::script_component>(entity).script;
		script->execute(delta_time);
	}
}
