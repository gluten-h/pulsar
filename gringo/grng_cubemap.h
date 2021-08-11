#pragma once

#include "grng_bindable.h"
#include "grng_bindable_entity.h"

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
	ID3D11Texture2D					*tex2d = NULL;
	ID3D11ShaderResourceView		*cubemap_srv = NULL;
	UINT							slot = 0u;


	void		remove_tex2d_memory();
	void		remove_cubemap_srv_memory();
	void		remove_cubemap_memory();
	void		set_cubemap_memory(LPCWSTR dds_path);

	void		create_dds_cubemap(LPCWSTR *wic_path, LPCWSTR output_dds_path);

	void		copy_assign(const grng_cubemap &c);

protected:
	void		remove_from_entities() override
	{
		for (auto &it : this->entities)
			it->_remove_bindable_ignore_entity(this);
		this->entities.clear();
	}

public:
	using GRNG_BINDABLE::bind;

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

	static grng_cubemap		*create();

	void		bind() const override
	{
		this->device_context->PSSetShaderResources(this->slot, 1u, &this->cubemap_srv);
		GRNG_BINDABLE::add_unbind(*this);
	}

	void		unbind() const override
	{
		this->device_context->PSSetShaderResources(this->slot, 0u, NULL);
	}
};

using GRNG_CUBEMAP = grng_cubemap;
