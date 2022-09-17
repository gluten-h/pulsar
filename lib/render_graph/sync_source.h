#pragma once

#include "source.h"
#include <type_traits>
#include "gfx_resources/sync_resource.h"
#include "exceptions/rg_exception.h"


namespace pulsar
{
	namespace rg
	{
		template <typename T>
		class sync_source : public pulsar::rg::source
		{
		private:
			T **mp_buffer = NULL;
			bool m_linked = false;

		public:
			sync_source<T> &operator=(const sync_source<T>&) = delete;
			sync_source<T> &operator=(sync_source<T>&&) = delete;
			sync_source(const sync_source<T>&) = delete;
			sync_source(sync_source<T>&&) = delete;

			sync_source(const std::string &name, T *&buffer) : pulsar::rg::source(name)
			{
				this->mp_buffer = &buffer;
			}
			~sync_source() = default;

			void	**yield_sync_data() override
			{
				if (this->m_linked)
					THROW_RG_EXC("The source " + this->name() + " has already been linked");
				this->m_linked = true;

				return ((void**)this->mp_buffer);
			}
		};
	}
}
