
#include "rasterizer_state.h"


void		PULSAR::RASTERIZER_STATE::remove_rs_memory()
{
	if (this->rs)
	{
		ULONG ref_count = this->rs->Release();
		if (ref_count == 0)
			this->rs = NULL;
	}
}

void		PULSAR::RASTERIZER_STATE::set_rs_memory(D3D11_FILL_MODE fill_mode, D3D11_CULL_MODE cull_mode)
{
	HRESULT hr;

	D3D11_RASTERIZER_DESC rsd;
	ZeroMemory(&rsd, sizeof(D3D11_RASTERIZER_DESC));

	rsd.FillMode = fill_mode;
	rsd.CullMode = cull_mode;
	rsd.FrontCounterClockwise = cull_mode == FALSE;
	rsd.DepthBias = 0;
	rsd.SlopeScaledDepthBias = 0.0f;
	rsd.DepthBiasClamp = 0.0f;
	rsd.DepthClipEnable = TRUE;
	rsd.ScissorEnable = FALSE;
	rsd.MultisampleEnable = FALSE;
	rsd.AntialiasedLineEnable = FALSE;

	GFX_ASSERT(this->device->CreateRasterizerState(&rsd, &this->rs));
}

void		PULSAR::RASTERIZER_STATE::set(D3D11_FILL_MODE fill_mode, D3D11_CULL_MODE cull_mode)
{
	this->remove_rs_memory();
	this->set_rs_memory(fill_mode, cull_mode);
}

ID3D11RasterizerState	*PULSAR::RASTERIZER_STATE::get()
{
	return (this->rs);
}


PULSAR::RASTERIZER_STATE	*PULSAR::RASTERIZER_STATE::create()
{
	return ((PULSAR::RASTERIZER_STATE*)PULSAR::BINDABLE::add_to_manager(new PULSAR::RASTERIZER_STATE));
}
