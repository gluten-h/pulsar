#pragma once

#include "source.h"
#include <type_traits>


namespace pulsar
{
	namespace rg
	{
		template <typename T>
		class async_source : public pulsar::rg::source
		{
		private:
			T **mp_buffer = NULL;

		public:
			async_source<T> &operator=(const async_source<T>&) = delete;
			async_source<T> &operator=(async_source<T>&&) = delete;
			async_source(const async_source<T>&) = delete;
			async_source(async_source<T>&&) = delete;
			async_source() = delete;
			async_source(const std::string &name, T *&buffer) : pulsar::rg::source(name)
			{
				this->mp_buffer = &buffer;
			}
			~async_source() = default;

			void	**yield_async_data() override
			{
				return ((void**)this->mp_buffer);
			}
		};
	}
}
