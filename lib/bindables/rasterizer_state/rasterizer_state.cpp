
#include "rasterizer_state.h"


PULSAR::rasterizer_state::rasterizer_state(D3D11_FILL_MODE fill_mode, D3D11_CULL_MODE cull_mode)
{
	this->create_rs(fill_mode, cull_mode);
}

PULSAR::rasterizer_state::~rasterizer_state()
{
	this->free();
}

void	PULSAR::rasterizer_state::bind() const
{
	PULSAR::gfx::get().device_context()->RSSetState(this->mp_rs);
}

void	PULSAR::rasterizer_state::unbind() const
{
	PULSAR::gfx::get().device_context()->RSSetState(NULL);
}
