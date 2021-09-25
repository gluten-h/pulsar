#pragma once

#include "rg_bindable_pass.h"
#include "def_shaders.h"
#include "def_rasterizer_states.h"


namespace PULSAR
{
	class RG_FULLSCREEN_PASS : public RG_BINDABLE_PASS, public PULSAR::PULSAR_ID3D
	{
	public:
		RG_FULLSCREEN_PASS(const std::string &name) : RG_BINDABLE_PASS(name), PULSAR::PULSAR_ID3D(){ }

		void	execute() override
		{
			this->bind();
			PULSAR::STD_BACK_FACE_CULL_RS.bind();
			PULSAR::FULLSCREEN_VS.bind(BIND_SCOPE::GLOBAL);
			this->device_context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
			this->device_context->Draw(4u, 0u);

			PULSAR::BINDABLE::unbind_all();
		}
	};
}
