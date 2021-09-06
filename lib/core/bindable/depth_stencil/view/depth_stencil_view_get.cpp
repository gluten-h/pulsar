
#include "depth_stencil_view.h"


ID3D11Texture2D		*PULSAR::DEPTH_STENCIL_VIEW::get_texture()
{
	return (this->ds_texture);
}

ID3D11DepthStencilView		*PULSAR::DEPTH_STENCIL_VIEW::get_view()
{
	return (this->ds_view);
}
