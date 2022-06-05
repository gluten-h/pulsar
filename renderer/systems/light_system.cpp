
#include "light_system.h"
#include "transform/transform_component.h"
#include "light/light_component.h"
#include "scene/scene.h"
#include "config/config.h"
#include "renderer/renderer.h"
#include "gfx/gfx.h"


pulsar::light_system::light_system(pulsar::ecs::registry *registry) : pulsar::ecs::system(registry)
{
	this->mp_deferred_frag_lights_cbuffer = new deferred_frag_lights_cbuffer(this->m_deferred_frag_lights, pulsar::DEFERRED_FRAG_LIGHTS_SLOT);
}

pulsar::light_system::~light_system()
{
	delete this->mp_deferred_frag_lights_cbuffer;
}

void	pulsar::light_system::execute(float delta_time)
{
	auto view = this->mp_registry->view<pulsar::transform_component, pulsar::light_component>();

	int i = 0;
	for (auto entity : view)
	{
		pulsar::transform &transform = this->mp_registry->get<pulsar::transform_component>(entity).transform;
		pulsar::light *light = this->mp_registry->get<pulsar::light_component>(entity).light;

		this->m_deferred_frag_lights.lights[i].type = (int)light->type();
		switch (light->type())
		{
			case pulsar::LIGHT_TYPE::POINT:
			{
				pulsar::point_light *point = (pulsar::point_light*)light;

				this->m_deferred_frag_lights.lights[i].pos_dir = transform.get_position();
				this->m_deferred_frag_lights.lights[i].color = point->color();
				this->m_deferred_frag_lights.lights[i].attenuation = XMFLOAT4(point->const_attenuation(), point->linear_attenuation(), point->quad_attenuation(), 1.0f);

				break;
			}
			case pulsar::LIGHT_TYPE::DIR:
			{
				pulsar::dir_light *dir = (pulsar::dir_light*)light;

				this->m_deferred_frag_lights.lights[i].pos_dir = transform.get_position();
				this->m_deferred_frag_lights.lights[i].color = dir->color();

				break;
			}
		}

		i++;
	}
	this->m_deferred_frag_lights.lights_count = i;

	this->mp_deferred_frag_lights_cbuffer->update();
	pulsar::renderer::instance().submit_deferred_frag_lights_cbuffer(this->mp_deferred_frag_lights_cbuffer);
}
