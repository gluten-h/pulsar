
#include "grng_render_texture.h"


ID3D11RenderTargetView			*grng_render_texture::get_render_target()
{
	return (this->texture_rtv);
}

ID3D11ShaderResourceView		*grng_render_texture::get_shader_resource()
{
	return (this->texture_srv);
}
