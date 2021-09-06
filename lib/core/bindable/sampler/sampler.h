#pragma once

#include "bindable.h"
#include "bindable_entity.h"


namespace PULSAR
{
	class SAMPLER : public PULSAR::BINDABLE
	{
	private:
		ID3D11SamplerState		*sampler = NULL;
		UINT					slot = 0u;


		void	set_sampler_memory();
		void	remove_sampler_memory();

		void	copy_assign(const SAMPLER &s);

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
		SAMPLER		&operator=(const SAMPLER &s);
		SAMPLER(const SAMPLER &s);
		SAMPLER(UINT slot = 0u);
		~SAMPLER();

		void	set_slot(UINT slot);

		static SAMPLER		*create();

		void	bind() const override
		{
			this->device_context->PSSetSamplers(this->slot, 1u, &this->sampler);
			BINDABLE::add_unbind(*this);
		}

		void	unbind() const override
		{
			this->device_context->PSGetSamplers(this->slot, 0u, NULL);
		}
	};
}
