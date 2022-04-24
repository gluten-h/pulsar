
#include "rasterizer_state.h"


void	PULSAR::rasterizer_state::free()
{
	if (this->mp_rs)
	{
		this->mp_rs->Release();
		this->mp_rs = NULL;
	}
}

void	PULSAR::rasterizer_state::create_rs(D3D11_FILL_MODE fill_mode, D3D11_CULL_MODE cull_mode)
{
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

	GFX_ASSERT(PULSAR::gfx::get().device()->CreateRasterizerState(&rsd, &this->mp_rs));
}

void	PULSAR::rasterizer_state::set(D3D11_FILL_MODE fill_mode, D3D11_CULL_MODE cull_mode)
{
	this->free();
	this->create_rs(fill_mode, cull_mode);
}

ID3D11RasterizerState	*PULSAR::rasterizer_state::get()
{
	return (this->mp_rs);
}
