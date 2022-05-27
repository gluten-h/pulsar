#pragma once

#include "render_graph/pass.h"
#include "gfx/gfx.h"
#include "config/rasterizer_state.h"
#include "config/shader.h"


namespace pulsar
{
	class fullscreen_pass : public pulsar::rg::pass
	{
	public:
		fullscreen_pass &operator=(const fullscreen_pass&) = delete;
		fullscreen_pass &operator=(fullscreen_pass&&) = delete;
		fullscreen_pass(const fullscreen_pass&) = delete;
		fullscreen_pass(fullscreen_pass&&) = delete;
		fullscreen_pass() = delete;
		fullscreen_pass(const std::string &name) : pulsar::rg::pass(name){ }
		~fullscreen_pass() = default;

		void	execute() override
		{
			pulsar::BACK_FACE_CULL_RS.bind();
			pulsar::FULLSCREEN_VS.bind();
			pulsar::gfx::instance().device_context()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
			pulsar::gfx::instance().device_context()->Draw(4u, 0u);

			pulsar::FULLSCREEN_VS.unbind();
			pulsar::BACK_FACE_CULL_RS.unbind();
		}
	};
}
