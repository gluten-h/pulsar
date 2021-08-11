#pragma once

#include "grng_rg_bindable_pass.h"
#include "grng_def_shaders.h"
#include "grng_def_rasterizer_states.h"


class grng_rg_fullscreen_pass : public GRNG_RG_BINDABLE_PASS, public GRNG_ID3D
{
public:
	grng_rg_fullscreen_pass(const std::string &name) : GRNG_RG_BINDABLE_PASS(name), GRNG_ID3D(){ }

	void		execute() override
	{
		this->bind();
		GRNG_STD_BACK_FACE_CULL_RS.bind();
		GRNG_FULLSCREEN_VS.bind(GRNG_BIND_SCOPE::GLOBAL);
		this->device_context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		this->device_context->Draw(4u, 0u);

		GRNG_BINDABLE::unbind_all();
	}
};

using GRNG_RG_FULLSCREEN_PASS = grng_rg_fullscreen_pass;
