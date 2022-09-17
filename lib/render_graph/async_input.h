#pragma once

#include "input.h"
#include "source.h"
#include "exceptions/rg_exception.h"
#include <string>
#include <type_traits>


namespace pulsar
{
	namespace rg
	{
		template <typename T>
		class async_input : public pulsar::rg::input
		{
		private:
			T **mp_target = NULL;

		public:
			async_input<T> &operator=(const async_input<T>&) = delete;
			async_input<T> &operator=(async_input<T>&&) = delete;
			async_input(const async_input<T>&) = delete;
			async_input(async_input<T>&&) = delete;
			async_input() = delete;
			async_input(const std::string &name, T *&target) : pulsar::rg::input(name)
			{
				this->mp_target = &target;
			}
			~async_input() = default;

			void	validate() const override
			{
				if (!this->mp_target)
					THROW_RG_EXC("The input " + this->name() + " is unlinked");
			}

			void	bind(pulsar::rg::source *source) override
			{
				T **source_data = (T**)source->get_async_data();
				if (typeid(**source_data).hash_code() != typeid(T).hash_code())
					THROW_RG_EXC("The " + this->name() + "\'s target type is incompatible with the " + source->name() + "\'s data type");

				*this->mp_target = *source_data;
			}
		};
	}
}
