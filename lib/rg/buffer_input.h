
#include "input.h"
#include "bindable/buffer_resource.h"
#include "buffer_source.h"
#include <type_traits>


namespace PULSAR
{
	namespace rg
	{
		template <typename T>
		class buffer_input : public PULSAR::rg::input
		{
		private:
			static_assert(std::is_base_of_v<PULSAR::buffer_resource, T>, "Buffer input target type must be a buffer_resource type");

		private:
			T **mp_source_buffer = NULL;

		public:
			buffer_input<T> &operator=(const buffer_input<T>&) = delete;
			buffer_input<T> &operator=(buffer_input<T>&&) = delete;
			buffer_input(const buffer_input<T>&) = delete;
			buffer_input(buffer_input<T>&&) = delete;
			buffer_input() = delete;
			buffer_input(const std::string &name, T *&target) : PULSAR::rg::input(name)
			{
				this->mp_source_buffer = &target;
			}
			~buffer_input() = default;

			void	validate() const override
			{
				if (!this->mp_source_buffer)
					THROW_RG_EXC("Unlinked input: " + this->name());
			}

			void	bind(PULSAR::rg::source *source) override
			{
				T **buffer = (T**)(source->yield_buffer());
				if (typeid(**buffer).hash_code() != typeid(T).hash_code())
					THROW_RG_EXC("Type of the buffer input " + this->name() + " is not compatible with type of the buffer source " + source->name());

				*this->mp_source_buffer = *buffer;
			}
		};
	}
}
