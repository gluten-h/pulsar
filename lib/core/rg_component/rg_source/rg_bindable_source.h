#pragma once

#include "rg_source.h"
#include "bindable.h"

#include <type_traits>


namespace PULSAR
{
	template<typename T>
	class RG_BINDABLE_SOURCE : public PULSAR::RG_SOURCE
	{
	private:
		static_assert(std::is_base_of_v<PULSAR::BINDABLE, T>, "RG_BINDABLE_SOURCE target type must be a BINDABLE type");

	private:
		T	**buffer = NULL;

	public:
		RG_BINDABLE_SOURCE(const std::string &name, T *&buffer) : PULSAR::RG_SOURCE(name)
		{
			this->buffer = &buffer;
		}

		static RG_BINDABLE_SOURCE<T>		*create(const std::string &name, T *&buffer)
		{
			return ((RG_BINDABLE_SOURCE<T>*)PULSAR::RG_COMPONENT::add_to_manager(new RG_BINDABLE_SOURCE<T>(name, buffer)));
		}

		PULSAR::BINDABLE	**yield_bindable() override
		{
			return ((PULSAR::BINDABLE**)this->buffer);
		}
	};
}
