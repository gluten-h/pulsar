#pragma once

#include <string>


namespace pulsar
{
	class sync_resource;

	namespace rg
	{
		class source
		{
		private:
			std::string m_name;

		protected:
			source(const std::string &name);

		public:
			source &operator=(const source&) = delete;
			source &operator=(source&&) = delete;
			source(const source&) = delete;
			source(source&&) = delete;
			source() = delete;
			virtual ~source() = default;

			const std::string	&name() const;

			virtual void	**get_async_data();
			virtual pulsar::sync_resource	**yield_sync_data();

			virtual void	validate() const;
		};
	}
}
