
#include "grng_depth_stencil_view.h"


ID3D11Texture2D				*grng_depth_stencil_view::get_texture()
{
	return (this->ds_texture);
}

ID3D11DepthStencilView		*grng_depth_stencil_view::get_view()
{
	return (this->ds_view);
}
