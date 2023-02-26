
#include "rasterizer_state.h"
#include "exceptions/gfx_exception.h"


pulsar::rasterizer_state::rasterizer_state(D3D11_CULL_MODE cull_mode, BOOL scissors_enabled, D3D11_FILL_MODE fill_mode)
{
	this->create_rs(cull_mode, scissors_enabled, fill_mode);
}

pulsar::rasterizer_state::~rasterizer_state()
{
	this->destroy_rs();
}

void	pulsar::rasterizer_state::create_rs(D3D11_CULL_MODE cull_mode, BOOL scissors_enabled, D3D11_FILL_MODE fill_mode)
{
	D3D11_RASTERIZER_DESC rsd;
	ZeroMemory(&rsd, sizeof(D3D11_RASTERIZER_DESC));

	rsd.FillMode = fill_mode;
	rsd.CullMode = cull_mode;
	rsd.DepthClipEnable = TRUE;
	rsd.ScissorEnable = scissors_enabled;

	GFX_ASSERT(pulsar::gfx::instance().device()->CreateRasterizerState(&rsd, &this->mp_rs));
}

void	pulsar::rasterizer_state::destroy_rs()
{
	if (this->mp_rs)
	{
		this->mp_rs->Release();
		this->mp_rs = NULL;
	}
}

void	pulsar::rasterizer_state::set(D3D11_CULL_MODE cull_mode, BOOL scissors_enabled, D3D11_FILL_MODE fill_mode)
{
	this->destroy_rs();
	this->create_rs(cull_mode, scissors_enabled, fill_mode);
}

void	pulsar::rasterizer_state::bind() const
{
	pulsar::gfx::instance().device_context()->RSSetState(this->mp_rs);
}

void	pulsar::rasterizer_state::unbind() const
{
	pulsar::gfx::instance().device_context()->RSSetState(NULL);
}
