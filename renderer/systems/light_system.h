#pragma once

#include "ecs/system.h"
#include "light/light.h"
#include "gfx_resources/frag_cbuffer.h"
#include "containers/array.h"


namespace pulsar
{
	class light_system : pulsar::ecs::system
	{
	private:
		using deferred_frag_lights_cbuffer = pulsar::frag_cbuffer<pulsar::deferred_frag_lights>;
		using submitted_lights = pulsar::array<pulsar::ecs::entity, pulsar::MAX_SCENE_LIGHTS_COUNT>;

		pulsar::deferred_frag_lights m_deferred_frag_lights;
		deferred_frag_lights_cbuffer *mp_deferred_frag_lights_cbuffer = NULL;

		submitted_lights m_submitted_lights;

	public:
		light_system();
		~light_system();

		void	execute(pulsar::ecs::registry &registry, float delta_time) override;
	};
}
