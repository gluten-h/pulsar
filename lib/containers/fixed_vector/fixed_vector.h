#pragma once

#include <cstddef>
#include <iterator>
#include <algorithm>
#include <stdexcept>


namespace PULSAR
{
	template <typename T, size_t MAX_SIZE>
	class FIXED_VECTOR
	{
	private:
		class ELEM
		{
		private:
			friend class FIXED_VECTOR;
			friend class FIXED_VECTOR::iterator;

		public:
			T		data;

			int		get_id() const
			{
				return (this->id);
			}

		private:
			int		id = -1;

			ELEM	 *next = NULL;
			ELEM	 *prev = NULL;
		};

	public:
		struct iterator
		{
			using iterator_category = std::forward_iterator_tag;
			using difference_type = std::ptrdiff_t;
			using value_type = ELEM;
			using pointer = ELEM*;
			using reference = ELEM&;

		private:
			pointer		m_ptr;

		public:
			iterator(pointer ptr)
			{
				this->m_ptr = ptr;
			}

			reference	operator*() const
			{
				return (*this->m_ptr);
			}
			pointer		operator->()
			{
				return (this->m_ptr);
			}

			iterator	&operator++()
			{
				this->m_ptr = this->m_ptr->next;
				return (*this);
			}
			iterator	operator++(int)
			{
				iterator temp = *this;
				++(*this);

				return (temp);
			}

			friend bool		operator==(const iterator &lhs, const iterator &rhs)
			{
				return (lhs.m_ptr == rhs.m_ptr);
			}
			friend bool		operator!=(const iterator &lhs, const iterator &rhs)
			{
				return (lhs.m_ptr != rhs.m_ptr);
			}
		};

	private:
		ELEM	data[MAX_SIZE];
		size_t	_size = 0u;

		size_t	iter_id = 0u;
		ELEM	*head_elem = NULL;
		ELEM	*tail_elem = NULL;


		void	move_iter_id()
		{
			if (this->iter_id >= MAX_SIZE || this->data[this->iter_id].id > -1)
			{
				int i = -1;
				while (++i < MAX_SIZE)
				{
					if (this->data[i].id == -1)
					{
						this->iter_id = i;
						break;
					}
				}
			}
		}
		void	remove_elem(unsigned int id)
		{
			ELEM *data_ptr = &this->data[id];

			if (data_ptr == this->head_elem)
			{
				this->head_elem = data_ptr->next;
			}
			else if (data_ptr == this->tail_elem)
			{
				this->tail_elem = data_ptr->prev;
			}
			else
			{
					ELEM *prev = data_ptr->prev;
					ELEM *next = data_ptr->next;
					prev->next = next;
					next->prev = prev;
			}

			data_ptr->id = -1;
			data_ptr->next = NULL;
			data_ptr->prev = NULL;
			this->_size--;
		}

	public:
		iterator	begin()
		{
			return (iterator(this->head_elem));
		}
		iterator	end()
		{
			return (iterator(NULL));
		}

		int		add(const T &value)
		{

			if (this->_size >= MAX_SIZE)
				return (-1);
			this->move_iter_id();

			int id = this->iter_id;
			this->data[id].data = value;
			this->data[id].id = id;

			if (!this->head_elem)
			{
				this->head_elem = &this->data[id];
				this->head_elem->next = NULL;
				this->head_elem->prev = NULL;
			}
			if (!this->tail_elem)
			{
				this->tail_elem = &this->data[id];
				this->tail_elem->next = NULL;
				this->tail_elem->prev = NULL;
			}
			else
			{
				this->tail_elem->next = &this->data[id];
				this->data[id].prev = this->tail_elem;
				this->tail_elem = this->tail_elem->next;
			}

			this->iter_id++;
			this->_size++;

			return (id);
		}
		void	remove(unsigned int id)
		{
			if (id >= MAX_SIZE || this->data[id].id == -1)
				return;
			this->remove_elem(id);
		}
		void	clear()
		{
			ELEM *elem = this->head_elem;
			while (elem)
			{
				elem->id = -1;
				elem = elem->next;
			}

			this->head_elem = NULL;
			this->tail_elem = NULL;
			this->iter_id = 0u;
			this->_size = 0u;
		}

		T	&at(unsigned int id)
		{
			if (id >= MAX_SIZE || this->data[id].id == -1)
				throw std::out_of_range("FIXED_VECTOR invalid id");
			return (this->data[id].data);
		}

		size_t	size() const
		{
			return (this->_size);
		}
	};
}
