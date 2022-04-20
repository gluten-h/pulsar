#pragma once

#include <cstddef>
#include <iterator>
#include <algorithm>
#include <stdexcept>


namespace PULSAR
{
	template <typename T, size_t MAX_SIZE>
	class fixed_vector
	{
	private:
		class elem
		{
		private:
			friend class fixed_vector;
			friend class fixed_vector::iterator;

		public:
			T		data;

			int		id() const
			{
				return (this->id);
			}

		private:
			int		m_id = -1;

			elem	 *next = NULL;
			elem	 *prev = NULL;
		};

	public:
		struct iterator
		{
			using iterator_category = std::forward_iterator_tag;
			using difference_type = std::ptrdiff_t;
			using value_type = elem;
			using pointer = elem*;
			using reference = elem&;

		private:
			pointer		m_ptr;

		public:
			iterator()
			{
				this->m_ptr = NULL;
			}
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
		elem	data[MAX_SIZE];
		size_t	_size = 0u;

		size_t	iter_id = 0u;
		elem	*head_elem = NULL;
		elem	*tail_elem = NULL;


		void	move_iter_id()
		{
			if (this->iter_id >= MAX_SIZE || this->data[this->iter_id].m_id > -1)
			{
				int i = -1;
				while (++i < MAX_SIZE)
				{
					if (this->data[i].m_id == -1)
					{
						this->iter_id = i;
						break;
					}
				}
			}
		}
		void	erase_elem(uint32_t id)
		{
			elem *data_ptr = &this->data[id];

			if (data_ptr == this->head_elem)
			{
				this->head_elem = data_ptr->next;
				if (this->head_elem)
					this->head_elem->prev = NULL;
			}
			else if (data_ptr == this->tail_elem)
			{
				this->tail_elem = data_ptr->prev;
				if (this->tail_elem)
					this->tail_elem->next = NULL;
			}
			else
			{
				elem *prev = data_ptr->prev;
				elem *next = data_ptr->next;
				prev->next = next;
				next->prev = prev;
			}

			data_ptr->m_id = -1;
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
			this->data[id].m_id = id;

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
		void	erase(uint32_t id)
		{
			if (id >= MAX_SIZE || this->data[id].m_id == -1)
				return;
			this->erase_elem(id);
		}
		void	clear()
		{
			elem *elem = this->head_elem;
			while (elem)
			{
				elem->m_id = -1;
				elem = elem->next;
			}

			this->head_elem = NULL;
			this->tail_elem = NULL;
			this->iter_id = 0u;
			this->_size = 0u;
		}

		T	&at(uint32_t id)
		{
			if (id >= MAX_SIZE || this->data[id].m_id == -1)
				throw std::out_of_range("fixed_vector: invalid id");
			return (this->data[id].data);
		}

		size_t	size() const
		{
			return (this->_size);
		}
	};
}
