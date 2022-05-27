#pragma once

#include <memory>
#include <string>
#include <vector>


namespace pulsar
{
	class dynamic_const_buffer;

	namespace dcb
	{
		class layout_elem;
		class raw_layout;
		class baked_layout;
		class layout_elem_ref;

		class buffer
		{
		private:
			friend class pulsar::dynamic_const_buffer;

		private:
			std::shared_ptr<pulsar::dcb::layout_elem>	mp_root;
			std::vector<char>	m_data;
			bool	m_is_modified = false;

		private:
			void	set_updated();

		public:
			buffer &operator=(const buffer&) = delete;
			buffer &operator=(buffer&&) = delete;
			buffer(const buffer&) = delete;
			buffer(buffer&&) = delete;
			buffer() = default;
			buffer(pulsar::dcb::raw_layout &&raw_layout);
			buffer(pulsar::dcb::baked_layout &&baked_layout);
			buffer(pulsar::dcb::raw_layout &raw_layout);
			buffer(const pulsar::dcb::baked_layout &baked_layout);
			~buffer() = default;

			pulsar::dcb::layout_elem_ref	operator[](const std::string &key);

			void	set_layout(pulsar::dcb::raw_layout &&raw_layout);
			void	set_layout(pulsar::dcb::baked_layout &&baked_layout);
			void	set_layout(pulsar::dcb::raw_layout &raw_layout);
			void	set_layout(const pulsar::dcb::baked_layout &baked_layout);

			const char	*data() const noexcept;
			size_t	size() const noexcept;
			bool	is_modified() const noexcept;
		};
	}
}
