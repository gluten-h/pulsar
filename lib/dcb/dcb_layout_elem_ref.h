#pragma once

#include "dcb/dcb_types.h"
#include "dcb/dcb_layout_elem.h"

#include <string>


namespace PULSAR
{
	namespace dcb
	{
		class layout_elem_ref
		{
		private:
			class ptr
			{
			private:
				friend class layout_elem_ref;

			private:
				layout_elem_ref		*mp_ref = NULL;

			public:
				template<typename T>
				operator	T*()
				{
					static_assert(PULSAR::dcb::reverse_attr_type<std::remove_const_t<T>>::is_valid, "Unsupported dcb type");
					return (&static_cast<T&>(*this->mp_ref));
				}

			private:
				ptr(layout_elem_ref *ref)
				{
					this->mp_ref = ref;
				}
			};

		private:
			const PULSAR::dcb::layout_elem	*mp_elem = NULL;
			char	*mp_data = NULL;
			bool	*mp_is_modified = NULL;

		public:
			layout_elem_ref(const PULSAR::dcb::layout_elem *layout_elem, char *data, bool *is_modified)
			{
				this->mp_elem = layout_elem;
				this->mp_data = data;
				this->mp_is_modified = is_modified;
			}

			layout_elem_ref		operator[](const std::string &key)
			{
				return (layout_elem_ref(&(*this->mp_elem)[key], this->mp_data, this->mp_is_modified));
			}

			layout_elem_ref::ptr	operator&()
			{
				return (layout_elem_ref::ptr(this));
			}

			template<typename T>
			operator	T&()
			{
				static_assert(PULSAR::dcb::reverse_attr_type<std::remove_const_t<T>>::is_valid, "Unsupported dcb type");
				return (*((T*)&this->mp_data[this->mp_elem->m_offset]));
			}

			template<typename T>
			T	&operator=(const T &rhs)
			{
				*this->mp_is_modified = true;
				return (static_cast<T&>(*this) = rhs);
			}


			bool	exists() const
			{
				return (this->mp_elem->exists());
			}
		};
	}
}
