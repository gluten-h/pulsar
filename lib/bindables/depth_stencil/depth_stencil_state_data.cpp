
#include "depth_stencil_state.h"
#include "exceptions/gfx_exception.h"


void	pulsar::depth_stencil_state::create_ds_state(BOOL depth_enable, D3D11_COMPARISON_FUNC depth_comp_func, D3D11_DEPTH_WRITE_MASK depth_write_mask)
{
	D3D11_DEPTH_STENCIL_DESC dsd;
	ZeroMemory(&dsd, sizeof(D3D11_DEPTH_STENCIL_DESC));

	dsd.DepthEnable = depth_enable;
	dsd.DepthFunc = depth_comp_func;
	dsd.DepthWriteMask = depth_write_mask;

	GFX_ASSERT(pulsar::gfx::instance().device()->CreateDepthStencilState(&dsd, &this->mp_ds_state));
}

void	pulsar::depth_stencil_state::free()
{
	if (this->mp_ds_state)
	{
		this->mp_ds_state->Release();
		this->mp_ds_state = NULL;
	}
}

void	pulsar::depth_stencil_state::set(BOOL depth_enable, D3D11_COMPARISON_FUNC depth_comp_func, D3D11_DEPTH_WRITE_MASK depth_write_mask)
{
	this->free();
	this->create_ds_state(depth_enable, depth_comp_func, depth_write_mask);
}

ID3D11DepthStencilState		*pulsar::depth_stencil_state::get()
{
	return (this->mp_ds_state);
}
