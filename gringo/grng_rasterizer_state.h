#pragma once

#include "grng_bindable.h"


class grng_rasterizer_state : public GRNG_BINDABLE
{
private:
	ID3D11RasterizerState		*rs = NULL;


	void		remove_rs_memory();
	void		set_rs_memory(D3D11_FILL_MODE fill_mode, D3D11_CULL_MODE cull_mode);

	void		copy_assign(const grng_rasterizer_state &rs);

public:
	grng_rasterizer_state		&operator=(const grng_rasterizer_state &rs);
	grng_rasterizer_state(const grng_rasterizer_state &rs);
	grng_rasterizer_state();
	grng_rasterizer_state(D3D11_FILL_MODE fill_mode, D3D11_CULL_MODE cull_mode);

	void					set(D3D11_FILL_MODE fill_mode, D3D11_CULL_MODE cull_mode);
	ID3D11RasterizerState	*get();

	static GRNG_BINDABLE	*create_manager_ptr();


	void		bind() const override
	{
		this->device_context->RSSetState(this->rs);
	}
};

using GRNG_RASTERIZER_STATE = grng_rasterizer_state;
