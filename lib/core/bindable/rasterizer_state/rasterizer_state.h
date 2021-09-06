#pragma once

#include "bindable.h"
#include "bindable_entity.h"


namespace PULSAR
{
	class RASTERIZER_STATE : public PULSAR::BINDABLE
	{
	private:
		ID3D11RasterizerState *rs = NULL;


		void		remove_rs_memory();
		void		set_rs_memory(D3D11_FILL_MODE fill_mode, D3D11_CULL_MODE cull_mode);

		void		copy_assign(const RASTERIZER_STATE &rs);

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
		RASTERIZER_STATE &operator=(const RASTERIZER_STATE &rs);
		RASTERIZER_STATE(const RASTERIZER_STATE &rs);
		RASTERIZER_STATE();
		RASTERIZER_STATE(D3D11_FILL_MODE fill_mode, D3D11_CULL_MODE cull_mode);
		~RASTERIZER_STATE();

		void					set(D3D11_FILL_MODE fill_mode, D3D11_CULL_MODE cull_mode);
		ID3D11RasterizerState *get();

		static RASTERIZER_STATE *create();

		void		bind() const override
		{
			this->device_context->RSSetState(this->rs);
			BINDABLE::add_unbind(*this);
		}

		void		unbind() const override
		{
			this->device_context->RSSetState(NULL);
		}
	};
}
