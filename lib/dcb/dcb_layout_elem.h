#pragma once

#include "dcb_types.h"

#include <cassert>
#include <memory>
#include <string>
#include <unordered_map>


namespace PULSAR
{
	namespace DCB
	{
		class layout_elem
		{
		private:
			friend class raw_layout;
			friend class baked_layout;
			friend class layout_elem_ref;

			struct extra_data
			{
				std::unordered_map<std::string, int>	m_keys;
				std::vector<PULSAR::DCB::layout_elem>	m_elems;
			};

		private:
			PULSAR::DCB::TYPE	m_type = PULSAR::DCB::Empty;
			std::shared_ptr<extra_data>	m_extra_data;
			size_t	m_offset = 0ull;

		public:
			PULSAR::DCB::layout_elem	&operator[](const std::string &key)
			{
				assert(("Getting access to non-struct element is forbidden", this->m_type == PULSAR::DCB::Struct));

				auto &extra_data = *this->m_extra_data;
				if (auto elem_it = extra_data.m_keys.find(key); elem_it != extra_data.m_keys.end())
					return (extra_data.m_elems[elem_it->second]);

				return (layout_elem::get_empty_elem());
			}
			const PULSAR::DCB::layout_elem	&operator[](const std::string &key) const
			{
				return (const_cast<layout_elem&>(*this)[key]);
			}

			// ADD AND RETURN PARENT LAYOUT_ELEM
			layout_elem		&add(PULSAR::DCB::TYPE type, const std::string &key)
			{
				this->add_data(type, key);
				return (*this);
			}

			// ADD  AND RETURN NEW LAYOUT_ELEM
			template <PULSAR::DCB::TYPE type>
			layout_elem		&add(const std::string &key)
			{
				this->add_data(type, key);
				return (this->m_extra_data->m_elems.back());
			}


			bool	exists() const
			{
				return (this->m_type != PULSAR::DCB::Empty);
			}

		private:
			layout_elem() = default;
			layout_elem(PULSAR::DCB::TYPE type)
			{
				assert(type != PULSAR::DCB::Empty);

				this->m_type = type;
				if (this->m_type == PULSAR::DCB::Struct)
					this->m_extra_data = std::make_shared<extra_data>();
			}

			static PULSAR::DCB::layout_elem		&get_empty_elem()
			{
				static layout_elem empty_elem;
				return (empty_elem);
			}

			void	add_data(PULSAR::DCB::TYPE type, const std::string &key)
			{
				assert(("Adding to non-struct element is forbidden", this->m_type == PULSAR::DCB::Struct));
				assert(("Invalid key name", this->validate_key(key)));

				auto &extra_data = *this->m_extra_data;
				assert(("Key already exists", (extra_data.m_keys.find(key) == extra_data.m_keys.end())));

				extra_data.m_elems.push_back(layout_elem(type));
				extra_data.m_keys[key] = extra_data.m_elems.size() - 1;
			}

			bool	validate_key(const std::string &key)
			{
				for (char c : key)
				{
					if (!std::isalnum(c) && c != '_')
						return (false);
				}

				return (!key.empty() && !std::isdigit(key.front()));
			}

			bool	crosses_boundary(size_t offset, size_t size) const noexcept
			{
				size_t end = offset + size;
				size_t b_start = offset / 16ull;
				size_t b_end = end / 16ull;

				return (size > 16ull || (b_start != b_end && end % 16ull != 0ull));
			}
			size_t	pad_boundary(size_t offset) const noexcept
			{
				return (offset + (16ull - offset % 16ull) % 16ull);
			}
			size_t	pad_if_crosses_boundary(size_t offset, size_t size) const noexcept
			{
				if (this->crosses_boundary(offset, size))
					return (this->pad_boundary(offset));
				return (offset);
			}


			// OFFSET BASED, FUNCTIONS WORK ONLY AFTER FINALIZATION
			size_t	get_offset_begin() const noexcept
			{
				return (this->m_offset);
			}
			size_t	get_offset_end() const noexcept
			{
				switch (this->m_type)
				{
				#define DCB_RDT_MACRO(t)													\
					case t:																	\
					{																		\
						return (this->m_offset + PULSAR::DCB::type_attr<t>::hlsl_size);		\
					}
					DCB_RAW_DATA_TYPES
				#undef DCB_RDT_MACRO
					case PULSAR::DCB::Struct:
					{
						return (this->pad_boundary(this->m_extra_data->m_elems.back().get_offset_end()));
					}
				}
			}
			size_t	size() const noexcept
			{
				return (this->get_offset_end() - this->get_offset_begin());
			}


			size_t	finalize_struct(size_t offset_in)
			{
				assert(("Empty struct is not allowed", this->m_extra_data->m_elems.size() > 0ull));

				auto &extra_data = *this->m_extra_data;
				this->m_offset = this->pad_boundary(offset_in);

				size_t offset = this->m_offset;
				for (auto &elem : extra_data.m_elems)
					offset = elem.finalize(offset);

				return (offset);
			}

			size_t	finalize(size_t offset_in)
			{
				switch (this->m_type)
				{
				#define DCB_RDT_MACRO(t)																					\
					case t:																									\
					{																										\
						this->m_offset = this->pad_if_crosses_boundary(offset_in, PULSAR::DCB::type_attr<t>::hlsl_size);	\
						return (this->m_offset + type_attr<t>::hlsl_size);													\
					}
					DCB_RAW_DATA_TYPES
				#undef DCB_RDT_MACRO
					case PULSAR::DCB::Struct:
					{
						return (this->finalize_struct(offset_in));
					}
					default:
					{
						assert(("Invalid DCB type", false));
						break;
					}
				}
			}
		};
	}
}
