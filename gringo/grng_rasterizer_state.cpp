
#include "grng_rasterizer_state.h"


void			grng_rasterizer_state::copy_assign(const grng_rasterizer_state &rs)
{
	this->rs = rs.rs;
	if (this->rs)
		this->rs->AddRef();
}


grng_rasterizer_state		&grng_rasterizer_state::operator=(const grng_rasterizer_state &rs)
{
	if (this->rs != rs.rs)
		this->remove_rs_memory();
	this->copy_assign(rs);

	return (*this);
}

grng_rasterizer_state::grng_rasterizer_state(const grng_rasterizer_state &rs) : GRNG_BINDABLE()
{
	this->type = GRNG_BINDABLE_TYPE::RASTERIZER_STATE;
	this->copy_assign(rs);
}

grng_rasterizer_state::grng_rasterizer_state() : GRNG_BINDABLE()
{
	this->type = GRNG_BINDABLE_TYPE::RASTERIZER_STATE;
}

grng_rasterizer_state::grng_rasterizer_state(D3D11_FILL_MODE fill_mode, D3D11_CULL_MODE cull_mode) : GRNG_BINDABLE()
{
	this->type = GRNG_BINDABLE_TYPE::RASTERIZER_STATE;
	this->set_rs_memory(fill_mode, cull_mode);
}

grng_rasterizer_state::~grng_rasterizer_state()
{
	this->remove_rs_memory();
}
