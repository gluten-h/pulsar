
#include "shader_texture.h"
#include "exceptions/gfx_exception.h"
#include "filesystem/filesystem.h"


pulsar::shader_texture	&pulsar::shader_texture::operator=(const shader_texture &st)
{
	this->copy_assign(st);
	return (*this);
}

pulsar::shader_texture::shader_texture(const shader_texture &st)
{
	this->copy_assign(st);
}

pulsar::shader_texture::shader_texture(const LPCWSTR file, UINT slot)
{
	this->create_srv(file);
	this->m_slot = slot;
}

pulsar::shader_texture::~shader_texture()
{
	this->destroy_srv();
}

void	pulsar::shader_texture::copy_assign(const pulsar::shader_texture &st)
{
	if (this->mp_texture != st.mp_texture)
	{
		this->destroy_texture();
		this->mp_texture = st.mp_texture;
		this->mp_texture->AddRef();
	}
	if (this->mp_srv != st.mp_srv)
	{
		this->destroy_srv();
		this->mp_srv = st.mp_srv;
		this->mp_srv->AddRef();
	}
}

void	pulsar::shader_texture::create_srv(const LPCWSTR file)
{
	GFX_ASSERT(CreateWICTextureFromFile(pulsar::gfx::instance().device(), pulsar::filesystem::absolute_path(file).c_str(), (ID3D11Resource**)&this->mp_texture, &this->mp_srv));
}

void	pulsar::shader_texture::destroy_srv()
{
	if (this->mp_srv)
	{
		this->mp_srv->Release();
		this->mp_srv = NULL;
	}
}

void	pulsar::shader_texture::set(const LPCWSTR file)
{
	this->destroy_texture();
	this->destroy_srv();
	this->create_srv(file);
}

void	pulsar::shader_texture::set_slot(UINT slot)
{
	this->m_slot = slot;
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
