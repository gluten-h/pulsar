#pragma once

#include <memory>
#include <string>
#include <vector>


namespace PULSAR
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
			friend class PULSAR::dynamic_const_buffer;

		private:
			std::shared_ptr<PULSAR::dcb::layout_elem>	mp_root;
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
			buffer(PULSAR::dcb::raw_layout &&raw_layout);
			buffer(PULSAR::dcb::baked_layout &&baked_layout);
			buffer(PULSAR::dcb::raw_layout &raw_layout);
			buffer(const PULSAR::dcb::baked_layout &baked_layout);
			~buffer() = default;

			PULSAR::dcb::layout_elem_ref	operator[](const std::string &key);

			void	set_layout(PULSAR::dcb::raw_layout &&raw_layout);
			void	set_layout(PULSAR::dcb::baked_layout &&baked_layout);
			void	set_layout(PULSAR::dcb::raw_layout &raw_layout);
			void	set_layout(const PULSAR::dcb::baked_layout &baked_layout);

			const char	*data() const noexcept;
			size_t	size() const noexcept;
			bool	is_modified() const noexcept;
		};
	}
}
