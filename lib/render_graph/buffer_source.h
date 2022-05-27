#pragma once

#include "source.h"
#include <type_traits>
#include "bindable/buffer_resource.h"
#include "exceptions/rg_exception.h"


namespace pulsar
{
	namespace rg
	{
		template <typename T>
		class buffer_source : public pulsar::rg::source
		{
		private:
			static_assert(std::is_base_of_v<pulsar::buffer_resource, T>, "Buffer source target type must be a buffer_resource type");

		private:
			T **mp_buffer = NULL;
			bool m_linked = false;

		public:
			buffer_source<T> &operator=(const buffer_source<T>&) = delete;
			buffer_source<T> &operator=(buffer_source<T>&&) = delete;
			buffer_source(const buffer_source<T>&) = delete;
			buffer_source(buffer_source<T>&&) = delete;

			buffer_source(const std::string &name, T *&buffer) : pulsar::rg::source(name)
			{
				this->mp_buffer = &buffer;
			}
			~buffer_source() = default;

			pulsar::buffer_resource		**yield_buffer_resource() override
			{
				if (this->m_linked)
					THROW_RG_EXC("Source " + this->name() + " has already been linked");
				this->m_linked = true;

				return ((pulsar::buffer_resource**)this->mp_buffer);
			}
		};
	}
}
