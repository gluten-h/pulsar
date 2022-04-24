
#include "shader_texture.h"
#include "filesystem/filesystem.h"


void	PULSAR::shader_texture::free()
{
	if (this->mp_texture)
	{
		this->mp_texture->Release();
		this->mp_texture = NULL;
	}
	if (this->mp_srv)
	{
		this->mp_srv->Release();
		this->mp_srv = NULL;
	}
}

void	PULSAR::shader_texture::create_shader_texture(const LPCWSTR file)
{
	GFX_ASSERT(CreateWICTextureFromFile(PULSAR::gfx::get().device(), PULSAR::filesystem::absolute_path(file).c_str(), (ID3D11Resource**)&this->mp_texture, &this->mp_srv));
}

void	PULSAR::shader_texture::set(const LPCWSTR file)
{
	this->free();
	this->create_shader_texture(file);
}

void	PULSAR::shader_texture::set_slot(UINT slot)
{
	this->m_slot = slot;
}
