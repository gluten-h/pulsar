
#include "grng_depth_stencil_state.h"


void		grng_depth_stencil_state::set_ds_memory(BOOL depth_enable, D3D11_COMPARISON_FUNC depth_comp_func, D3D11_DEPTH_WRITE_MASK depth_write_mask)
{
	HRESULT hr;

	D3D11_DEPTH_STENCIL_DESC dsd;
	ZeroMemory(&dsd, sizeof(D3D11_DEPTH_STENCIL_DESC));

	dsd.DepthEnable = depth_enable;
	dsd.DepthFunc = depth_comp_func;
	dsd.DepthWriteMask = depth_write_mask;

	GRNG_GFX_ASSERT(this->device->CreateDepthStencilState(&dsd, &this->ds_state));
}

void		grng_depth_stencil_state::remove_ds_memory()
{
	if (this->ds_state)
	{
		ULONG ref_count = this->ds_state->Release();
		if (ref_count == 0)
			this->ds_state = NULL;
	}
}

void		grng_depth_stencil_state::set(BOOL depth_enable, D3D11_COMPARISON_FUNC depth_comp_func, D3D11_DEPTH_WRITE_MASK depth_write_mask)
{
	this->remove_ds_memory();
	this->set_ds_memory(depth_enable, depth_comp_func, depth_write_mask);
}

ID3D11DepthStencilState		*grng_depth_stencil_state::get_state()
{
	return (this->ds_state);
}

GRNG_BINDABLE		*grng_depth_stencil_state::create_manager_ptr()
{
	grng_depth_stencil_state *dss = new grng_depth_stencil_state;

	return (dss);
}
