
#include "shader_texture.h"


pulsar::shader_texture	&pulsar::shader_texture::operator=(const pulsar::shader_texture &st)
{
	this->copy_assign(st);
	return (*this);
}

pulsar::shader_texture::shader_texture(const pulsar::shader_texture &st)
{
	this->copy_assign(st);
}

pulsar::shader_texture::shader_texture(const LPCWSTR file, UINT slot)
{
	this->create_shader_texture(file);
	this->set_slot(slot);
}

pulsar::shader_texture::~shader_texture()
{
	this->free();
}

void	pulsar::shader_texture::bind() const
{
	pulsar::gfx::instance().device_context()->PSSetShaderResources(this->m_slot, 1u, &this->mp_srv);
}

void	pulsar::shader_texture::unbind() const
{
	ID3D11ShaderResourceView *null_ptr[1] = { NULL };
	pulsar::gfx::instance().device_context()->PSSetShaderResources(this->m_slot, 1u, null_ptr);
}
