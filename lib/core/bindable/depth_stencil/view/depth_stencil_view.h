#pragma once

#include "bindable.h"
#include "bindable_entity.h"


namespace PULSAR
{
	class DEPTH_STENCIL_VIEW : public PULSAR::BINDABLE, public PULSAR::BUFFER_RESOURCE
	{
	private:
		ID3D11Texture2D			*ds_texture = NULL;
		ID3D11DepthStencilView	*ds_view = NULL;


		void		set_ds_memory(float width, float height);

		void		remove_ds_texture_memory();
		void		remove_ds_view_memory();
		void		remove_ds_memory();

		void		copy_assign(const PULSAR::DEPTH_STENCIL_VIEW &dsv);

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
		DEPTH_STENCIL_VIEW		&operator=(const DEPTH_STENCIL_VIEW &dsv);
		DEPTH_STENCIL_VIEW(const DEPTH_STENCIL_VIEW &dsv);
		DEPTH_STENCIL_VIEW();
		DEPTH_STENCIL_VIEW(float width, float height);
		~DEPTH_STENCIL_VIEW();

		void						set(float width, float height);

		ID3D11Texture2D				*get_texture();
		ID3D11DepthStencilView		*get_view();

		static DEPTH_STENCIL_VIEW	*create();

		void		clear() override
		{
			this->device_context->ClearDepthStencilView(this->ds_view, D3D11_CLEAR_DEPTH, 1.0f, 0u);
		}

		void		bind() const override
		{
		}
		void		unbind() const override
		{
		}
	};

	using DS_VIEW = DEPTH_STENCIL_VIEW;
}
