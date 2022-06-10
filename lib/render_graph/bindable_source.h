#pragma once

#include "source.h"
#include "bindable/bindable.h"
#include <type_traits>


namespace pulsar
{
	namespace rg
	{
		template <typename T>
		class bindable_source : public pulsar::rg::source
		{
		private:
			static_assert(std::is_base_of_v<pulsar::bindable, T>, "Bindable source target type must be a bindable type");

			T **mp_buffer = NULL;

		public:
			bindable_source<T> &operator=(const bindable_source<T>&) = delete;
			bindable_source<T> &operator=(bindable_source<T>&&) = delete;
			bindable_source(const bindable_source<T>&) = delete;
			bindable_source(bindable_source<T>&&) = delete;
			bindable_source() = delete;
			bindable_source(const std::string &name, T *&buffer) : pulsar::rg::source(name)
			{
				this->mp_buffer = &buffer;
			}
			~bindable_source() = default;

			pulsar::bindable	**yield_bindable() override
			{
				return ((pulsar::bindable**)this->mp_buffer);
			}
		};
	}
}
