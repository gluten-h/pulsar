
#include "render_texture.h"


ID3D11RenderTargetView		*PULSAR::RENDER_TEXTURE::get_render_target()
{
	return (this->texture_rtv);
}

ID3D11ShaderResourceView	*PULSAR::RENDER_TEXTURE::get_shader_resource()
{
	return (this->texture_srv);
}
