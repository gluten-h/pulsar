
#include "light_system.h"
#include "metadata/metadata_component.h"
#include "transform/transform_component.h"
#include "light/light_component.h"
#include "scene/scene.h"
#include "config/config.h"
#include "renderer/renderer.h"
#include "gfx/gfx.h"


pulsar::light_system::light_system()
{
	this->mp_deferred_frag_lights_cbuffer = new deferred_frag_lights_cbuffer(&this->m_deferred_frag_lights, pulsar::CBUFFER_TYPE::DYNAMIC, pulsar::FRAG_DEFERRED_LIGHTS_SLOT);
}

pulsar::light_system::~light_system()
{
	delete this->mp_deferred_frag_lights_cbuffer;
}

void	pulsar::light_system::execute(pulsar::ecs::registry &registry, float delta_time)
{
	auto &renderer = pulsar::renderer::instance();

	this->m_submitted_lights.clear();

	int light_id = 0;
	auto view = registry.view<pulsar::metadata_component, pulsar::transform_component, pulsar::light_component>();
	for (auto entity : view)
	{
		pulsar::mask &mask = view.get<pulsar::metadata_component>(entity).mask;
		pulsar::transform &transform = view.get<pulsar::transform_component>(entity).transform;
		pulsar::light *light = view.get<pulsar::light_component>(entity).light;

		this->m_deferred_frag_lights.lights[light_id].type = (int)light->type();
		switch (light->type())
		{
			case pulsar::LIGHT_TYPE::POINT:
			{
				pulsar::point_light *point = (pulsar::point_light*)light;

				this->m_deferred_frag_lights.lights[light_id].pos_dir = transform.get_position();
				this->m_deferred_frag_lights.lights[light_id].color = point->color();
				this->m_deferred_frag_lights.lights[light_id].attenuation = XMFLOAT4(point->const_attenuation(), point->linear_attenuation(), point->quad_attenuation(), 1.0f);

				break;
			}
			case pulsar::LIGHT_TYPE::DIR:
			{
				pulsar::dir_light *dir = (pulsar::dir_light*)light;

				this->m_deferred_frag_lights.lights[light_id].pos_dir = transform.get_position();
				this->m_deferred_frag_lights.lights[light_id].color = dir->color();

				break;
			}
		}
		int i = -1;
		while (++i < light->shadow_map()->draw_calls())
			this->m_deferred_frag_lights.lights[light_id].shadow_map_uv[i] = light->shadow_map()->uv(i);

		this->m_submitted_lights.push_back(entity);

		light_id++;
	}
	this->m_deferred_frag_lights.lights_count = light_id;
	this->mp_deferred_frag_lights_cbuffer->update();

	renderer.submit_deferred_frag_lights_cbuffer(this->mp_deferred_frag_lights_cbuffer);
	renderer.submit_lights(&this->m_submitted_lights);
}
