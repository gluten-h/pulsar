#pragma once

#include "bindable.h"
#include "bindable_entity.h"
#include "filesystem.h"

#include <string>


namespace PULSAR
{
	class TEXTURE : public PULSAR::BINDABLE
	{
	private:
		ID3D11Texture2D				*texture2d = NULL;
		ID3D11ShaderResourceView	*texture_srv = NULL;
		UINT						slot = 0u;


		void	remove_texture2d_memory();
		void	remove_texture_srv_memory();
		void	remove_texture_memory();
		void	set_texture_memory(const LPCWSTR file);

		void	copy_assign(const TEXTURE &t);

	protected:
		void	remove_from_entities() override
		{
			for (auto &it : this->entities)
				it->_remove_bindable_ignore_entity(this);
			this->entities.clear();
		}

	public:
		using PULSAR::BINDABLE::bind;

	public:
		TEXTURE		&operator=(const TEXTURE &t);
		TEXTURE(const TEXTURE &t);
		TEXTURE();
		TEXTURE(const LPCWSTR file, UINT slot = 0u);
		~TEXTURE();

		void	set(const LPCWSTR file);
		void	set_slot(UINT slot);

		static TEXTURE		*create();

		void	bind() const override
		{
			this->device_context->PSSetShaderResources(this->slot, 1u, &this->texture_srv);
			BINDABLE::add_unbind(*this);
		}

		void	unbind() const override
		{
			this->device_context->PSGetShaderResources(this->slot, 0u, NULL);
		}
	};
}
