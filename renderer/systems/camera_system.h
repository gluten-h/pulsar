#pragma once

#include "ecs/system.h"
#include "camera/camera.h"
#include "gfx_resources/vert_cbuffer.h"
#include "gfx_resources/frag_cbuffer.h"


namespace pulsar
{
	class camera_system : public pulsar::ecs::system
	{
	private:
		using vert_camera_cbuffer = pulsar::vert_cbuffer<pulsar::vert_camera>;
		using frag_camera_cbuffer = pulsar::frag_cbuffer<pulsar::frag_camera>;

		pulsar::vert_camera m_vert_camera;
		vert_camera_cbuffer m_vert_camera_cbuffer;

		pulsar::frag_camera m_frag_camera;
		frag_camera_cbuffer m_frag_camera_cbuffer;

	public:
		camera_system();
		~camera_system() = default;

		void	execute(pulsar::ecs::registry &registry, float delta_time) override;
	};
}
