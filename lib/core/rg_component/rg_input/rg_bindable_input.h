#pragma once

#include "rg_input.h"
#include "bindable.h"

#include <type_traits>


namespace PULSAR
{
	template<typename T>
	class RG_BINDABLE_INPUT : public PULSAR::RG_INPUT
	{
	private:
		static_assert(std::is_base_of_v<BINDABLE, T>, "RG_BINDABLE_INPUT target type must be a BINDABLE type");

	private:
		T	**source_bindable = NULL;

	public:
		RG_BINDABLE_INPUT(const std::string &name, T *&target) : PULSAR::RG_INPUT(name)
		{
			this->source_bindable = &target;
		}

		static RG_BINDABLE_INPUT<T>		*create(const std::string &name, T *&target)
		{
			return ((RG_BINDABLE_INPUT<T>*)PULSAR::RG_COMPONENT::add_to_manager(new RG_BINDABLE_INPUT<T>(name, target)));
		}

		void	validate() const override
		{
			if (!this->source_buffer)
				THROW_RG_EXC("RG_BINDABLE_INPUT \"" + this->get_name() + "\": Unlinked input");
		}

		void		bind(PULSAR::RG_SOURCE *source) override
		{
			T **buffer = (T **)(source->yield_bindable());
			if (typeid(**buffer).hash_code() != typeid(T).hash_code())
			{
				THROW_RG_EXC("RG_BINDABLE_INPUT \"" + this->get_name() + "\": RG_INPUT \"" + this->get_name() + "\" of type \"" + typeid(T).name() + "\" is no compatible with \""
							 + this->get_source_pass_name() + "." + this->get_source_name() + "\" of type \"" + typeid(**buffer).name() + "\"");
			}

			*this->source_buffer = *buffer;
		}
	};
}
