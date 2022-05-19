#pragma once

#include "render_graph/pass.h"
#include "gfx/gfx.h"
#include "config/rasterizer_state.h"
#include "config/shader.h"


namespace PULSAR
{
	class fullscreen_pass : public PULSAR::rg::pass
	{
	public:
		fullscreen_pass &operator=(const fullscreen_pass&) = delete;
		fullscreen_pass &operator=(fullscreen_pass&&) = delete;
		fullscreen_pass(const fullscreen_pass&) = delete;
		fullscreen_pass(fullscreen_pass&&) = delete;
		fullscreen_pass() = delete;
		fullscreen_pass(const std::string &name) : PULSAR::rg::pass(name){ }
		~fullscreen_pass() = default;

		void	execute(float delta_time) override
		{
			PULSAR::BACK_FACE_CULL_RS.bind();
			PULSAR::FULLSCREEN_VS.bind();
			PULSAR::gfx::get().device_context()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
			PULSAR::gfx::get().device_context()->Draw(4u, 0u);
		}
	};
}
