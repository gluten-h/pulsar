
#include "cubemap.h"
#include "filesystem/filesystem.h"
#include "exceptions/gfx_exception.h"


void	pulsar::cubemap::copy_assign(const pulsar::cubemap &c)
{
	if (this->mp_texture != c.mp_texture)
	{
		this->free_texture();
		this->mp_texture = c.mp_texture;
		this->mp_texture->AddRef();
	}
	if (this->mp_srv != c.mp_srv)
	{
		this->free_srv();
		this->mp_srv = c.mp_srv;
		this->mp_srv->AddRef();
	}
}

void	pulsar::cubemap::free_texture()
{
	if (this->mp_texture)
	{
		this->mp_texture->Release();
		this->mp_texture = NULL;
	}
}

void	pulsar::cubemap::free_srv()
{
	if (this->mp_srv)
	{
		this->mp_srv->Release();
		this->mp_srv = NULL;
	}
}

void	pulsar::cubemap::free()
{
	this->free_texture();
	this->free_srv();
}

void	pulsar::cubemap::create_cubemap(LPCWSTR dds_path)
{
	GFX_ASSERT(CreateDDSTextureFromFileEx(pulsar::gfx::instance().device(), pulsar::filesystem::absolute_path(dds_path).c_str(), 6u, D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0u,
												D3D11_RESOURCE_MISC_TEXTURECUBE, false, (ID3D11Resource**)&this->mp_texture, &this->mp_srv));
}

void	pulsar::cubemap::set(LPCWSTR *wic_path, LPCWSTR output_dds_path, pulsar::CUBEMAP_DDS dds_behavior)
{
	this->free();

	switch (dds_behavior)
	{
		case pulsar::CUBEMAP_DDS::OVERWRITE:
		{
			this->save_dds_cubemap(wic_path, output_dds_path);
			break;
		}
		case pulsar::CUBEMAP_DDS::KEEP_IF_EXISTS:
		{
			if (std::filesystem::exists(pulsar::filesystem::absolute_path(output_dds_path)))
				break;
			this->save_dds_cubemap(wic_path, output_dds_path);
			break;
		}
	}
	this->create_cubemap(output_dds_path);
}

void		pulsar::cubemap::set(LPCWSTR dds_path)
{
	this->free();
	this->create_cubemap(dds_path);
}

void		pulsar::cubemap::set_slot(UINT slot)
{
	this->m_slot = slot;
}
