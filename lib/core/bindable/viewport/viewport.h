#pragma once

#include "bindable.h"
#include "bindable_entity.h"


namespace PULSAR
{
	class VIEWPORT : public PULSAR::BINDABLE
	{
	private:
		D3D11_VIEWPORT		viewport = { 0 };


		void	set_viewport_memory(float width, float height, float min_depth, float max_depth);
		void	copy_assign(const VIEWPORT &v);

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
		VIEWPORT	&operator=(const VIEWPORT &v);
		VIEWPORT(const VIEWPORT &v);
		VIEWPORT();
		VIEWPORT(float width, float height, float min_depth = 0.0f, float max_depth = 1.0f);

		void			set(float width, float height, float min_depth = 0.0f, float max_depth = 1.0f);
		D3D11_VIEWPORT	&get();

		static VIEWPORT		*create();

		void	bind() const override
		{
			this->device_context->RSSetViewports(1u, &this->viewport);
			BINDABLE::add_unbind(*this);
		}

		void	unbind() const override
		{
			this->device_context->RSSetViewports(0u, NULL);
		}
	};
}
