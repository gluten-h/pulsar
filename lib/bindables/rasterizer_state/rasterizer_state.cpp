
#include "rasterizer_state.h"


pulsar::rasterizer_state::rasterizer_state(D3D11_FILL_MODE fill_mode, D3D11_CULL_MODE cull_mode)
{
	this->create_rs(fill_mode, cull_mode);
}

pulsar::rasterizer_state::~rasterizer_state()
{
	this->free();
}

void	pulsar::rasterizer_state::bind() const
{
	pulsar::gfx::instance().device_context()->RSSetState(this->mp_rs);
}

void	pulsar::rasterizer_state::unbind() const
{
	pulsar::gfx::instance().device_context()->RSSetState(NULL);
}
