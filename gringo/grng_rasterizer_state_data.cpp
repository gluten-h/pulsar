
#include "grng_rasterizer_state.h"


void		grng_rasterizer_state::remove_rs_memory()
{
	if (this->rs)
	{
		ULONG ref_count = this->rs->Release();
		if (ref_count == 0)
			this->rs = NULL;
	}
}

void		grng_rasterizer_state::set_rs_memory(D3D11_FILL_MODE fill_mode, D3D11_CULL_MODE cull_mode)
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

	HRESULT hr = this->device->CreateRasterizerState(&rsd, &this->rs);
}

void					grng_rasterizer_state::set(D3D11_FILL_MODE fill_mode, D3D11_CULL_MODE cull_mode)
{
	this->remove_rs_memory();
	this->set_rs_memory(fill_mode, cull_mode);
}

ID3D11RasterizerState	*grng_rasterizer_state::get()
{
	return (this->rs);
}

GRNG_BINDABLE		*grng_rasterizer_state::create_manager_ptr()
{
	grng_rasterizer_state *rs = new grng_rasterizer_state;

	return (rs);
}
