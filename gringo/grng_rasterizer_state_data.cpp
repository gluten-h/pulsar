
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

	GRNG_GFX_ASSERT(this->device->CreateRasterizerState(&rsd, &this->rs));
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


grng_rasterizer_state	*grng_rasterizer_state::create()
{
	grng_rasterizer_state *rs = new grng_rasterizer_state;
	rs->id = GRNG_BM.add(rs);
	if (rs->id == -1)
	{
		delete rs;
		return (NULL);
	}
	rs->is_alloc = true;

	return (rs);
}
