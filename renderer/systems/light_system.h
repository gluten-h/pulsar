#pragma once

#include "ecs/system.h"
#include "light/light.h"
#include "const_buffers/frag_const_buffer.h"


namespace pulsar
{
	class light_system : pulsar::ecs::system
	{
	private:
		using deferred_frag_lights_cbuffer = pulsar::frag_const_buffer<pulsar::deferred_frag_lights>;

		pulsar::deferred_frag_lights m_deferred_frag_lights;
		deferred_frag_lights_cbuffer *mp_deferred_frag_lights_cbuffer = NULL;

	public:
		light_system() = delete;
		light_system(pulsar::ecs::registry *registry);
		~light_system();

		void	execute(float delta_time) override;
	};
}
