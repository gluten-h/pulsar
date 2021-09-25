#pragma once

#include "rg_source.h"
#include "bindable.h"

#include <type_traits>


namespace PULSAR
{
	template<typename T>
	class RG_BUFFER_SOURCE : public PULSAR::RG_SOURCE
	{
	private:
		static_assert(std::is_base_of_v<PULSAR::BUFFER_RESOURCE, T>, "RG_BUFFER_SOURCE target type must be a BUFFER_RESOURCE type");

	private:
		T		**buffer = NULL;
		bool	linked = false;

	public:
		RG_BUFFER_SOURCE(const std::string &name, T *&buffer) : PULSAR::RG_SOURCE(name)
		{
			this->buffer = &buffer;
		}

		static RG_BUFFER_SOURCE<T>		*create(const std::string &name, T *&source_buffer)
		{
			return ((RG_BUFFER_SOURCE<T>*)PULSAR::RG_COMPONENT::add_to_manager(new RG_BUFFER_SOURCE<T>(name, source_buffer)));
		}

		PULSAR::BUFFER_RESOURCE		**yield_buffer() override
		{
			if (this->linked)
				THROW_RG_EXC("RG_BUFFER_SOURCE \"" + this->get_name() + "\": Already linked");
			this->linked = true;

			return ((PULSAR::BUFFER_RESOURCE**)this->buffer);
		}
	};
}
