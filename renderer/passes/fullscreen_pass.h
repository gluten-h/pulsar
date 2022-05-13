#pragma once

#include "rg/pass.h"
#include "_gfx/_gfx.h"
#include "config/rasterizer_state.h"
#include "config/shader.h"


namespace PULSAR
{
	class fullscreen_pass : public PULSAR::rg::pass
	{
	public:
		fullscreen_pass(const std::string &name) : PULSAR::rg::pass(name){ }

		void	execute() override
		{
			PULSAR::BACK_FACE_CULL_RS.bind();
			PULSAR::FULLSCREEN_VS.bind();
			PULSAR::gfx::get().device_context()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
			PULSAR::gfx::get().device_context()->Draw(4u, 0u);
		}
	};
}
