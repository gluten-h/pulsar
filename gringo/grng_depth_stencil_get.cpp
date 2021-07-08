
#include "grng_depth_stencil.h"


ID3D11Texture2D				*grng_depth_stencil::get_texture() const
{
	return (this->ds_texture);
}

ID3D11DepthStencilState		*grng_depth_stencil::get_ds_state() const
{
	return (this->ds_state);
}

ID3D11DepthStencilView		*grng_depth_stencil::get_ds_view() const
{
	return (this->ds_view);
}
