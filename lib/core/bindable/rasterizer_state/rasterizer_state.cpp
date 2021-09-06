
#include "rasterizer_state.h"


void	PULSAR::RASTERIZER_STATE::copy_assign(const RASTERIZER_STATE &rs)
{
	this->rs = rs.rs;
	if (this->rs)
		this->rs->AddRef();
}


PULSAR::RASTERIZER_STATE	&PULSAR::RASTERIZER_STATE::operator=(const RASTERIZER_STATE &rs)
{
	if (this->rs != rs.rs)
		this->remove_rs_memory();
	this->copy_assign(rs);

	return (*this);
}

PULSAR::RASTERIZER_STATE::RASTERIZER_STATE(const RASTERIZER_STATE &rs) : PULSAR::BINDABLE()
{
	this->type = PULSAR::BINDABLE_TYPE::RASTERIZER_STATE;
	this->copy_assign(rs);
}

PULSAR::RASTERIZER_STATE::RASTERIZER_STATE() : PULSAR::BINDABLE()
{
	this->type = PULSAR::BINDABLE_TYPE::RASTERIZER_STATE;
}

PULSAR::RASTERIZER_STATE::RASTERIZER_STATE(D3D11_FILL_MODE fill_mode, D3D11_CULL_MODE cull_mode) : PULSAR::BINDABLE()
{
	this->type = PULSAR::BINDABLE_TYPE::RASTERIZER_STATE;
	this->set_rs_memory(fill_mode, cull_mode);
}

PULSAR::RASTERIZER_STATE::~RASTERIZER_STATE()
{
	this->remove_rs_memory();
}
