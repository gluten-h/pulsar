
#include "cubemap.h"
#include "exceptions/gfx_exception.h"
#include "filesystem/filesystem.h"


pulsar::cubemap		&pulsar::cubemap::operator=(const pulsar::cubemap &c)
{
	this->copy_assign(c);
	return (*this);
}

pulsar::cubemap::cubemap(const cubemap &c)
{
	this->copy_assign(c);
}

pulsar::cubemap::cubemap(LPCWSTR *files, LPCWSTR output_dds_path, FILE_CREATION behavior, UINT slot)
{
	this->set(files, output_dds_path, behavior);
	this->m_slot = slot;
}

pulsar::cubemap::cubemap(LPCWSTR dds_file, UINT slot)
{
	this->set(dds_file);
	this->m_slot = slot;
}

pulsar::cubemap::~cubemap()
{
	this->destroy_srv();
}

void	pulsar::cubemap::copy_assign(const cubemap &c)
{
	if (this->mp_texture != c.mp_texture)
	{
		this->destroy_texture();
		this->mp_texture = c.mp_texture;
		this->mp_texture->AddRef();
	}
	if (this->mp_srv != c.mp_srv)
	{
		this->destroy_srv();
		this->mp_srv = c.mp_srv;
		this->mp_srv->AddRef();
	}
}

void	pulsar::cubemap::convert_to_dds(LPCWSTR *files, LPCWSTR output_dds_path)
{
	std::unique_ptr<ScratchImage> scratch_img[6];
	Image img[6];

	uint8_t *pix_data = NULL;

	for (size_t i = 0; i < 6; i++)
	{
		scratch_img[i] = std::make_unique<ScratchImage>();
		GFX_ASSERT(LoadFromWICFile(pulsar::filesystem::absolute_path(files[i]).c_str(), WIC_FLAGS_NONE, NULL, *scratch_img[i]));
		img[i] = *scratch_img[i]->GetImage(0, 0, 0);
	}

	TexMetadata meta_data;
	meta_data.width = img[0].width;
	meta_data.height = img[0].height;
	meta_data.depth = 1;
	meta_data.arraySize = 6;
	meta_data.mipLevels = 1;
	meta_data.miscFlags = TEX_MISC_TEXTURECUBE;
	meta_data.miscFlags2 = TEX_ALPHA_MODE_OPAQUE;
	meta_data.format = img[0].format;
	meta_data.dimension = TEX_DIMENSION_TEXTURE2D;

	GFX_ASSERT(SaveToDDSFile(img, 6u, meta_data, DDS_FLAGS_NONE, pulsar::filesystem::absolute_path(output_dds_path).c_str()));
}

void	pulsar::cubemap::create_srv(LPCWSTR dds_file)
{
	GFX_ASSERT(CreateDDSTextureFromFileEx(pulsar::gfx::instance().device(),
											pulsar::filesystem::absolute_path(dds_file).c_str(), 6u,
											D3D11_USAGE_IMMUTABLE, D3D11_BIND_SHADER_RESOURCE, 0u,
											D3D11_RESOURCE_MISC_TEXTURECUBE, false,
											(ID3D11Resource**)&this->mp_texture, &this->mp_srv));
}

void	pulsar::cubemap::destroy_srv()
{
	if (this->mp_srv)
	{
		int a = this->mp_srv->Release();
		this->mp_srv = NULL;
	}
}

void	pulsar::cubemap::set(LPCWSTR *files, LPCWSTR output_dds_path, FILE_CREATION behavior)
{
	this->destroy_texture();
	this->destroy_srv();

	switch (behavior)
	{
		case pulsar::FILE_CREATION::OVERWRITE:
		{
			this->convert_to_dds(files, output_dds_path);
			break;
		}
		case pulsar::FILE_CREATION::KEEP_IF_EXISTS:
		{
			if (std::filesystem::exists(pulsar::filesystem::absolute_path(output_dds_path)))
				break;
			this->convert_to_dds(files, output_dds_path);
			break;
		}
	}

	this->create_srv(output_dds_path);
}

void	pulsar::cubemap::set(LPCWSTR dds_file)
{
	this->destroy_texture();
	this->destroy_srv();
	this->create_srv(dds_file);
}

void	pulsar::cubemap::set_slot(UINT slot)
{
	this->m_slot = slot;
}

void	pulsar::cubemap::bind() const
{
	pulsar::gfx::instance().device_context()->PSSetShaderResources(this->m_slot, 1u, &this->mp_srv);
}

void	pulsar::cubemap::unbind() const
{
	ID3D11ShaderResourceView *null[1] = { NULL };
	pulsar::gfx::instance().device_context()->PSSetShaderResources(this->m_slot, 1u, null);
}
