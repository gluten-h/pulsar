#pragma once

#include "grng_bindable.h"

#include <filesystem>
#include <string>


enum class GRNG_CUBEMAP_DDS
{
	OVERWRITE,
	KEEP_IF_EXISTS
};


class grng_cubemap : GRNG_BINDABLE
{
private:
	friend class grng_manager_ptr;

private:
	ID3D11Texture2D					*tex2d = NULL;
	ID3D11ShaderResourceView		*cubemap_srv = NULL;
	UINT							slot = 0u;


	void		remove_tex2d_memory();
	void		remove_cubemap_srv_memory();
	void		remove_cubemap_memory();
	void		set_cubemap_memory(LPCWSTR dds_path);

	void		create_dds_cubemap(LPCWSTR *wic_path, LPCWSTR output_dds_path);

	void		copy_assign(const grng_cubemap &c);

	static GRNG_BINDABLE		*create_manager_ptr();

public:
	grng_cubemap	&operator=(const grng_cubemap &c);
	grng_cubemap(const grng_cubemap &c);
	grng_cubemap();
	grng_cubemap(LPCWSTR *wic_path, LPCWSTR output_dds_path, GRNG_CUBEMAP_DDS dds_behavior = GRNG_CUBEMAP_DDS::OVERWRITE, UINT slot = 0u);
	grng_cubemap(LPCWSTR dds_path, UINT slot = 0u);
	~grng_cubemap();

	void		set(LPCWSTR *wic_path, LPCWSTR output_dds_path, GRNG_CUBEMAP_DDS dds_behavior = GRNG_CUBEMAP_DDS::OVERWRITE);
	void		set(LPCWSTR dds_path);
	void		set_slot(UINT slot);

	void		bind() const override
	{
		this->device_context->PSSetShaderResources(this->slot, 1u, &this->cubemap_srv);
	}
};

using GRNG_CUBEMAP = grng_cubemap;
