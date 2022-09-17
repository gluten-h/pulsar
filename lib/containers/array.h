#pragma once

#include <memory>


namespace pulsar
{
	template <typename T, size_t MAX_SIZE>
	class array
	{
	private:
		T m_data[MAX_SIZE];
		size_t m_size = 0u;

	public:
		array<T, MAX_SIZE> &operator=(const array<T, MAX_SIZE>&) = delete;
		array<T, MAX_SIZE> &operator=(array<T, MAX_SIZE>&&) = delete;
		array(const array<T, MAX_SIZE>&) = delete;
		array(array<T, MAX_SIZE>&&) = delete;
		array() = default;
		~array() = default;

		const T		&operator[](size_t id) const
		{
			return (this->m_data[id]);
		}

		size_t	size() const
		{
			return (this->m_size);
		}
		size_t	max_size() const
		{
			return (MAX_SIZE);
		}

		T	*data()
		{
			return (this->m_data);
		}
		const T		*data() const
		{
			return (this->m_data);
		}

		void	clear()
		{
			this->m_size = 0u;
		}

		void	push_back(const T &elem)
		{
			this->m_data[this->m_size++] = elem;
		}
		void	push_back(T &&elem)
		{
			this->m_data[this->m_size++] = std::move(elem);
		}
	};
}
