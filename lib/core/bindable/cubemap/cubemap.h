#pragma once

#include "bindable.h"
#include "bindable_entity.h"
#include "filesystem.h"


namespace PULSAR
{
	enum class CUBEMAP_DDS
	{
		OVERWRITE,
		KEEP_IF_EXISTS
	};


	class CUBEMAP : PULSAR::BINDABLE
	{
	private:
		ID3D11Texture2D				*tex2d = NULL;
		ID3D11ShaderResourceView	*cubemap_srv = NULL;
		UINT						slot = 0u;


		void		remove_tex2d_memory();
		void		remove_cubemap_srv_memory();
		void		remove_cubemap_memory();
		void		set_cubemap_memory(LPCWSTR dds_path);

		void		create_dds_cubemap(LPCWSTR *wic_path, LPCWSTR output_dds_path);

		void		copy_assign(const CUBEMAP &c);

	protected:
		void		remove_from_entities() override
		{
			for (auto &it : this->entities)
				it->_remove_bindable_ignore_entity(this);
			this->entities.clear();
		}

	public:
		using PULSAR::BINDABLE::bind;

	public:
		CUBEMAP		&operator=(const CUBEMAP &c);
		CUBEMAP(const CUBEMAP &c);
		CUBEMAP();
		CUBEMAP(LPCWSTR *wic_path, LPCWSTR output_dds_path, CUBEMAP_DDS dds_behavior = CUBEMAP_DDS::OVERWRITE, UINT slot = 0u);
		CUBEMAP(LPCWSTR dds_path, UINT slot = 0u);
		~CUBEMAP();

		void		set(LPCWSTR *wic_path, LPCWSTR output_dds_path, CUBEMAP_DDS dds_behavior = CUBEMAP_DDS::OVERWRITE);
		void		set(LPCWSTR dds_path);
		void		set_slot(UINT slot);

		static CUBEMAP		*create();

		void		bind() const override
		{
			this->device_context->PSSetShaderResources(this->slot, 1u, &this->cubemap_srv);
			BINDABLE::add_unbind(*this);
		}

		void		unbind() const override
		{
			ID3D11ShaderResourceView *null_ptr[1] = { NULL };
			this->device_context->PSSetShaderResources(this->slot, 1u, null_ptr);
		}
	};
}
