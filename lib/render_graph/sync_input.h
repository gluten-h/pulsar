#pragma once

#include "input.h"
#include "gfx_resources/sync_resource.h"
#include "source.h"
#include "exceptions/rg_exception.h"
#include <type_traits>


namespace pulsar
{
	namespace rg
	{
		template <typename T>
		class sync_input : public pulsar::rg::input
		{
		private:
			static_assert(std::is_base_of_v<pulsar::sync_resource, T>, "The sync_input target type must inherit the sync_resource class");

			T **mp_target = NULL;

		public:
			sync_input<T> &operator=(const sync_input<T>&) = delete;
			sync_input<T> &operator=(sync_input<T>&&) = delete;
			sync_input(const sync_input<T>&) = delete;
			sync_input(sync_input<T>&&) = delete;
			sync_input() = delete;
			sync_input(const std::string &name, T *&target) : pulsar::rg::input(name)
			{
				this->mp_target = &target;
			}
			~sync_input() = default;

			void	validate() const override
			{
				if (!this->mp_target)
					THROW_RG_EXC("The input " + this->name() + " is unlinked");
			}

			void	bind(pulsar::rg::source *source) override
			{
				T **source_data = (T**)(source->yield_sync_data());
				if (typeid(**source_data).hash_code() != typeid(T).hash_code())
					THROW_RG_EXC("The " + this->name() + "\'s target type is incompatible with the " + source->name() + "\'s data type");

				*this->mp_target = *source_data;
			}
		};
	}
}
