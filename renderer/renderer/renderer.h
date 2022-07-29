#pragma once

#include "utils/singleton.h"
#include "transform/transform.h"
#include "camera/camera.h"
#include "light/light.h"
#include "gfx_resources/viewport.h"
#include "gfx_resources/vert_cbuffer.h"
#include "gfx_resources/frag_cbuffer.h"


namespace pulsar
{
	class transform;

	class renderer : public pulsar::singleton<renderer>
	{
	private:
		using vert_camera_cbuffer = pulsar::vert_cbuffer<pulsar::vert_camera>;
		using frag_camera_cbuffer = pulsar::frag_cbuffer<pulsar::frag_camera>;
		using deferred_frag_lights_cbuffer = pulsar::frag_cbuffer<pulsar::deferred_frag_lights>;

		// TODO: think about ability to render scene through multiple cameras,
		// and how it should be stored inside the renderer (array of submitted cameras?)
		pulsar::viewport *mp_main_camera_viewport = NULL;
		vert_camera_cbuffer *mp_vert_camera_cbuffer = NULL;
		frag_camera_cbuffer *mp_frag_camera_cbuffer = NULL;
		deferred_frag_lights_cbuffer *mp_deferred_frag_lights_cbuffer = NULL;

	public:
		renderer &operator=(const renderer&) = delete;
		renderer &operator=(renderer&&) = delete;
		renderer(const renderer&) = delete;
		renderer(renderer&&) = delete;
		renderer() = default;
		~renderer() = default;

		pulsar::viewport	*get_main_camera_viewport();
		pulsar::vert_cbuffer<pulsar::vert_camera>	*get_vert_camera_cbuffer();
		pulsar::frag_cbuffer<pulsar::frag_camera>	*get_frag_camera_cbuffer();
		pulsar::frag_cbuffer<pulsar::deferred_frag_lights>	*get_deferred_frag_lights_cbuffer();

		void	submit_main_camera_viewport(pulsar::viewport *viewport);
		void	submit_vert_camera_cbuffer(pulsar::vert_cbuffer<pulsar::vert_camera> *cbuffer);
		void	submit_frag_camera_cbuffer(pulsar::frag_cbuffer<pulsar::frag_camera> *cbuffer);
		void	submit_deferred_frag_lights_cbuffer(pulsar::frag_cbuffer<pulsar::deferred_frag_lights> *cbuffer);
	};
}
