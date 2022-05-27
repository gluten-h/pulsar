
#include "shader_texture.h"
#include "filesystem/filesystem.h"
#include "exceptions/gfx_exception.h"


void	pulsar::shader_texture::copy_assign(const pulsar::shader_texture &st)
{
	if (this->mp_texture != st.mp_texture)
	{
		this->free_texture();
		this->mp_texture = st.mp_texture;
		this->mp_texture->AddRef();
	}
	if (this->mp_srv != st.mp_srv)
	{
		this->free_srv();
		this->mp_srv = st.mp_srv;
		this->mp_srv->AddRef();
	}
}

void	pulsar::shader_texture::free_texture()
{
	if (this->mp_texture)
	{
		this->mp_texture->Release();
		this->mp_texture = NULL;
	}
}

void	pulsar::shader_texture::free_srv()
{
	if (this->mp_srv)
	{
		this->mp_srv->Release();
		this->mp_srv = NULL;
	}
}

void	pulsar::shader_texture::free()
{
	this->free_texture();
	this->free_srv();
}

void	pulsar::shader_texture::create_shader_texture(const LPCWSTR file)
{
	GFX_ASSERT(CreateWICTextureFromFile(pulsar::gfx::instance().device(), pulsar::filesystem::absolute_path(file).c_str(), (ID3D11Resource**)&this->mp_texture, &this->mp_srv));
}

void	pulsar::shader_texture::set(const LPCWSTR file)
{
	this->free();
	this->create_shader_texture(file);
}

void	pulsar::shader_texture::set_slot(UINT slot)
{
	this->m_slot = slot;
}
