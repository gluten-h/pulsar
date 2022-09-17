#pragma once

#include "utils/singleton.h"
#include "config/config.h"
#include "rq/viewport_rq.h"
#include "rq/shadows_rq.h"
#include "transform/transform.h"
#include "camera/camera.h"
#include "light/light.h"
#include "mask/mask.h"
#include "gfx_resources/viewport.h"
#include "gfx_resources/vert_cbuffer.h"
#include "gfx_resources/frag_cbuffer.h"
#include "containers/array.h"
#include "ecs/types.h"


namespace pulsar
{
	class transform;

	class renderer : public pulsar::singleton<renderer>
	{
	private:
		using vert_camera_cbuffer = pulsar::vert_cbuffer<pulsar::vert_camera>;
		using frag_camera_cbuffer = pulsar::frag_cbuffer<pulsar::frag_camera>;
		using deferred_frag_lights_cbuffer = pulsar::frag_cbuffer<pulsar::deferred_frag_lights>;
		using submitted_lights = pulsar::array<pulsar::ecs::entity, pulsar::MAX_SCENE_LIGHTS_COUNT>;

		pulsar::viewport_rq m_viewport_rq;
		pulsar::shadows_rq m_shadows_rq;

		// TODO: think about ability to render scene through multiple cameras,
		// and how it should be stored inside the renderer (array of submitted cameras?)
		pulsar::viewport *mp_main_camera_viewport = NULL;
		vert_camera_cbuffer *mp_vert_camera_cbuffer = NULL;
		frag_camera_cbuffer *mp_frag_camera_cbuffer = NULL;
		deferred_frag_lights_cbuffer *mp_deferred_frag_lights_cbuffer = NULL;
		submitted_lights *mp_submitted_lights = NULL;

	public:
		renderer &operator=(const renderer&) = delete;
		renderer &operator=(renderer&&) = delete;
		renderer(const renderer&) = delete;
		renderer(renderer&&) = delete;
		renderer() = default;
		~renderer() = default;

		pulsar::viewport_rq	&viewport_rq();
		pulsar::shadows_rq	&shadows_rq();

		pulsar::viewport	*get_main_camera_viewport();
		pulsar::vert_cbuffer<pulsar::vert_camera>	*get_vert_camera_cbuffer();
		pulsar::frag_cbuffer<pulsar::frag_camera>	*get_frag_camera_cbuffer();
		pulsar::frag_cbuffer<pulsar::deferred_frag_lights>	*get_deferred_frag_lights_cbuffer();
		pulsar::array<pulsar::ecs::entity, pulsar::MAX_SCENE_LIGHTS_COUNT>		*get_submitted_lights();

		void	submit_main_camera_viewport(pulsar::viewport *viewport);
		void	submit_vert_camera_cbuffer(pulsar::vert_cbuffer<pulsar::vert_camera> *cbuffer);
		void	submit_frag_camera_cbuffer(pulsar::frag_cbuffer<pulsar::frag_camera> *cbuffer);
		void	submit_deferred_frag_lights_cbuffer(pulsar::frag_cbuffer<pulsar::deferred_frag_lights> *cbuffer);
		void	submit_lights(pulsar::array<pulsar::ecs::entity, pulsar::MAX_SCENE_LIGHTS_COUNT> *lights);
	};
}
