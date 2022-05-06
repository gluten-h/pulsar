
#include "source.h"
#include "bindable/buffer_resource.h"
#include <type_traits>


namespace PULSAR
{
	namespace rg
	{
		template <typename T>
		class buffer_source : public PULSAR::rg::source
		{
		private:
			static_assert(std::is_base_of_v<PULSAR::buffer_resource, T>, "Buffer source target type must be a buffer_resource type");

		private:
			T **mp_buffer = NULL;
			bool m_linked = false;

		public:
			buffer_source<T> &operator=(const buffer_source<T>&) = delete;
			buffer_source<T> &operator=(buffer_source<T>&&) = delete;
			buffer_source(const buffer_source<T>&) = delete;
			buffer_source(buffer_source<T>&&) = delete;
			buffer_source() = delete;
			buffer_source(const std::string &name, T *&buffer) : PULSAR::rg::source(name)
			{
				*this->mp_buffer = &buffer;
			}
			~buffer_source() = default;

			PULSAR::buffer_resource		**yield_buffer() override
			{
				if (this->m_linked)
					THROW_RG_EXC("Source " + this->name() + " has already been linked");
				this->m_linked = true;

				return ((PULSAR::buffer_resource**)this->mp_buffer);
			}
		};
	}
}
