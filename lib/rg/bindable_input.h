
#include "input.h"
#include "exceptions/rg_exception.h"
#include <string>
#include <type_traits>


namespace PULSAR
{
	namespace rg
	{
		template <typename T>
		class bindable_input : public PULSAR::rg::input
		{
		private:
			static_assert(std::is_base_of_v<PULSAR::buffer_resource, T>, "Bindable input target type must be a bindable type");

		private:
			T **mp_source_bindable = NULL;

		public:
			bindable_input<T> &operator=(const bindable_input<T>&) = delete;
			bindable_input<T> &operator=(bindable_input<T>&&) = delete;
			bindable_input(const bindable_input<T>&) = delete;
			bindable_input(bindable_input<T>&&) = delete;
			bindable_input() = delete;
			bindable_input(const std::string &name, T *&target) : PULSAR::rg::input(name)
			{
				*this->mp_source_bindable = &target;
			}
			~bindable_input() = default;

			void	validate() const override
			{
				if (!this->mp_source_bindable)
					THROW_RG_EXC("Unlinked input: " + this->name());
			}

			void	bind(PULSAR::rg::source *source) override
			{
				T **bindable = (T**)source->yield_bindable();
				if (typeid(**bindable).hash_code() != typeid(T).hash_code())
					THROW_RG_EXC("Type of the bindable input " + this->name() + " is not compatible with type of the bindable source " + source->name());

				*this->mp_source_bindable = *bindable;
			}
		};
	}
}
