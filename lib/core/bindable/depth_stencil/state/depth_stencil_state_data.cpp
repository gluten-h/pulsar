
#include "depth_stencil_state.h"


void		PULSAR::DEPTH_STENCIL_STATE::set_ds_memory(BOOL depth_enable, D3D11_COMPARISON_FUNC depth_comp_func, D3D11_DEPTH_WRITE_MASK depth_write_mask)
{
	HRESULT hr;

	D3D11_DEPTH_STENCIL_DESC dsd;
	ZeroMemory(&dsd, sizeof(D3D11_DEPTH_STENCIL_DESC));

	dsd.DepthEnable = depth_enable;
	dsd.DepthFunc = depth_comp_func;
	dsd.DepthWriteMask = depth_write_mask;

	GFX_ASSERT(this->device->CreateDepthStencilState(&dsd, &this->ds_state));
}

void		PULSAR::DEPTH_STENCIL_STATE::remove_ds_memory()
{
	if (this->ds_state)
	{
		ULONG ref_count = this->ds_state->Release();
		if (ref_count == 0)
			this->ds_state = NULL;
	}
}

void		PULSAR::DEPTH_STENCIL_STATE::set(BOOL depth_enable, D3D11_COMPARISON_FUNC depth_comp_func, D3D11_DEPTH_WRITE_MASK depth_write_mask)
{
	this->remove_ds_memory();
	this->set_ds_memory(depth_enable, depth_comp_func, depth_write_mask);
}

ID3D11DepthStencilState		*PULSAR::DEPTH_STENCIL_STATE::get_state()
{
	return (this->ds_state);
}


PULSAR::DEPTH_STENCIL_STATE		*PULSAR::DEPTH_STENCIL_STATE::create()
{
	return ((PULSAR::DEPTH_STENCIL_STATE*)PULSAR::BINDABLE::add_to_manager(new PULSAR::DEPTH_STENCIL_STATE));
}
