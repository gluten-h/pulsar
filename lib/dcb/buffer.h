#pragma once

#include "dcb/raw_layout.h"
#include "dcb/baked_layout.h"
#include "dcb/layout_elem_ref.h"

#include <string>
#include <vector>


namespace PULSAR
{
	class dynamic_const_buffer;

	namespace dcb
	{
		class buffer
		{
		private:
			friend class PULSAR::BINDABLE;
			friend class PULSAR::dynamic_const_buffer;

		private:
			std::shared_ptr<PULSAR::dcb::layout_elem>	mp_root;
			std::vector<char>	m_data;
			bool	m_is_modified = false;


			void	set_updated()
			{
				this->m_is_modified = false;
			}

		public:
			buffer(){ }
			buffer(PULSAR::dcb::raw_layout &&raw_layout) : buffer(PULSAR::dcb::baked_layout(std::move(raw_layout))){ }
			buffer(PULSAR::dcb::baked_layout &&baked_layout)
			{
				this->set_layout(std::move(baked_layout));
			}
			buffer(PULSAR::dcb::raw_layout &raw_layout) : buffer(PULSAR::dcb::baked_layout(raw_layout)){ }
			buffer(const PULSAR::dcb::baked_layout &baked_layout)
			{
				this->set_layout(baked_layout);
			}
			buffer(const buffer &b)
			{
				this->mp_root = b.mp_root;
				this->m_data = b.m_data;
			}

			PULSAR::dcb::layout_elem_ref	operator[](const std::string &key)
			{
				return (PULSAR::dcb::layout_elem_ref(&(*this->mp_root)[key], this->m_data.data(), &this->m_is_modified));
			}

			void	set_layout(PULSAR::dcb::raw_layout &&raw_layout)
			{
				this->set_layout(PULSAR::dcb::baked_layout(std::move(raw_layout)));
			}
			void	set_layout(PULSAR::dcb::baked_layout &&baked_layout)
			{
				this->m_data.resize(baked_layout.size(), 0);
				this->mp_root = baked_layout.yield_root();
			}
			void	set_layout(PULSAR::dcb::raw_layout &raw_layout)
			{
				this->set_layout(PULSAR::dcb::baked_layout(raw_layout));
			}
			void	set_layout(const PULSAR::dcb::baked_layout &baked_layout)
			{
				this->m_data.resize(baked_layout.size(), 0);
				this->mp_root = baked_layout.share_root();
			}

			const char	*data() const noexcept
			{
				return (this->m_data.data());
			}
			size_t	size() const noexcept
			{
				return (this->m_data.size());
			}

			bool	is_modified() const noexcept
			{
				return (this->m_is_modified);
			}
		};
	}
}
