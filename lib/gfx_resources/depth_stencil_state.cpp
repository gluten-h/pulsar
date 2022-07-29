
#include "depth_stencil_state.h"
#include "exceptions/gfx_exception.h"


pulsar::depth_stencil_state::depth_stencil_state(BOOL depth_enable, D3D11_COMPARISON_FUNC comp_func, D3D11_DEPTH_WRITE_MASK write_mask)
{
	this->create_dss(depth_enable, comp_func, write_mask);
}

pulsar::depth_stencil_state::~depth_stencil_state()
{
	this->destroy_dss();
}

void	pulsar::depth_stencil_state::create_dss(BOOL depth_enable, D3D11_COMPARISON_FUNC comp_func, D3D11_DEPTH_WRITE_MASK write_mask)
{
	D3D11_DEPTH_STENCIL_DESC dsd;
	ZeroMemory(&dsd, sizeof(D3D11_DEPTH_STENCIL_DESC));

	dsd.DepthEnable = depth_enable;
	dsd.DepthFunc = comp_func;
	dsd.DepthWriteMask = write_mask;

	GFX_ASSERT(pulsar::gfx::instance().device()->CreateDepthStencilState(&dsd, &this->mp_dss));
}

void	pulsar::depth_stencil_state::destroy_dss()
{
	if (this->mp_dss)
	{
		this->mp_dss->Release();
		this->mp_dss = NULL;
	}
}

void	pulsar::depth_stencil_state::set(BOOL depth_enable, D3D11_COMPARISON_FUNC comp_func, D3D11_DEPTH_WRITE_MASK write_mask)
{
	this->destroy_dss();
	this->create_dss(depth_enable, comp_func, write_mask);
}

ID3D11DepthStencilState		*pulsar::depth_stencil_state::dss()
{
	return (this->mp_dss);
}

void	pulsar::depth_stencil_state::bind() const
{
	pulsar::gfx::instance().device_context()->OMSetDepthStencilState(this->mp_dss, 1u);
}

void	pulsar::depth_stencil_state::unbind() const
{
	pulsar::gfx::instance().device_context()->OMSetDepthStencilState(NULL, 1u);
}
