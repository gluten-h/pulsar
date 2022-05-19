
#include "shader_texture.h"


PULSAR::shader_texture	&PULSAR::shader_texture::operator=(const PULSAR::shader_texture &st)
{
	this->copy_assign(st);
	return (*this);
}

PULSAR::shader_texture::shader_texture(const PULSAR::shader_texture &st)
{
	this->copy_assign(st);
}

PULSAR::shader_texture::shader_texture(const LPCWSTR file, UINT slot)
{
	this->create_shader_texture(file);
	this->set_slot(slot);
}

PULSAR::shader_texture::~shader_texture()
{
	this->free();
}

void	PULSAR::shader_texture::bind() const
{
	PULSAR::gfx::get().device_context()->PSSetShaderResources(this->m_slot, 1u, &this->mp_srv);
}

void	PULSAR::shader_texture::unbind() const
{
	ID3D11ShaderResourceView *null_ptr[1] = { NULL };
	PULSAR::gfx::get().device_context()->PSSetShaderResources(this->m_slot, 1u, null_ptr);
}
