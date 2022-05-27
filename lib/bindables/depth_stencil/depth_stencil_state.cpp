
#include "depth_stencil_state.h"


pulsar::depth_stencil_state::depth_stencil_state()
{

}

pulsar::depth_stencil_state::depth_stencil_state(BOOL depth_enable, D3D11_COMPARISON_FUNC depth_comp_func, D3D11_DEPTH_WRITE_MASK depth_write_mask)
{
	this->set(depth_enable, depth_comp_func, depth_write_mask);
}

pulsar::depth_stencil_state::~depth_stencil_state()
{
	this->free();
}

void	pulsar::depth_stencil_state::bind() const
{
	pulsar::gfx::instance().device_context()->OMSetDepthStencilState(this->mp_ds_state, 1u);
}

void	pulsar::depth_stencil_state::unbind() const
{
	pulsar::gfx::instance().device_context()->OMSetDepthStencilState(NULL, 1u);
}
