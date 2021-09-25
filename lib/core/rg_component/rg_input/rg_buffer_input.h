#pragma once

#include "rg_input.h"
#include "bindable.h"

#include <type_traits>


namespace PULSAR
{
	template<typename T>
	class RG_BUFFER_INPUT : public PULSAR::RG_INPUT
	{
	private:
		static_assert(std::is_base_of_v<BUFFER_RESOURCE, T>, "RG_BUFFER_INPUT target type must be a BUFFER_RESOURCE type");

	private:
		T	**source_buffer = NULL;

	public:
		RG_BUFFER_INPUT(const std::string &name, T *&target) : PULSAR::RG_INPUT(name)
		{
			this->source_buffer = &target;
		}

		static RG_BUFFER_INPUT<T>		*create(const std::string &name, T *&target)
		{
			return ((RG_BUFFER_INPUT<T>*)PULSAR::RG_COMPONENT::add_to_manager(new RG_BUFFER_INPUT<T>(name, target)));
		}

		void	validate() const override
		{
			if (!this->source_buffer)
				THROW_RG_EXC("RG_BUFFER_INPUT \"" + this->get_name() + "\": Unlinked input \"" + this->get_name() + "\"");
		}

		void	bind(PULSAR::RG_SOURCE *source) override
		{
			T **buffer = (T**)(source->yield_buffer());
			if (typeid(**buffer).hash_code() != typeid(T).hash_code())
			{
				THROW_RG_EXC("RG_BUFFER_INPUT \"" + this->get_name() + "\": RG_INPUT \"" + this->get_name() + "\" of type \"" + typeid(T).name() + "\" is no compatible with \""
							 + this->get_source_pass_name() + "." + this->get_source_name() + "\" of type \"" + typeid(**buffer).name() + "\"");
			}

			*this->source_buffer = *buffer;
		}
	};
}
