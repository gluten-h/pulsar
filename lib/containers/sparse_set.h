#pragma once

#include <cassert>
#include <type_traits>
#include <limits>
#include <vector>
#include <algorithm>


namespace PULSAR
{
	template <typename T>
	class sparse_set
	{
		static_assert(std::is_unsigned<T>::value, "Specified type has to be unsigned");

	private:
		static const T INVALID_ID = (std::numeric_limits<T>::max)();

		std::vector<T> m_dense;
		std::vector<T> m_sparse;

	public:
		sparse_set() = default;
		sparse_set(size_t preallocated_size)
		{
			this->m_sparse.resize(preallocated_size, INVALID_ID);
		}
		~sparse_set() = default;

		typename std::vector<T>::iterator	begin()
		{
			return (this->m_dense.begin());
		}
		const typename std::vector<T>::iterator	begin() const
		{
			return (this->m_dense.begin());
		}

		typename std::vector<T>::iterator	end()
		{
			return (this->m_dense.end());
		}
		const typename std::vector<T>::iterator	end() const
		{
			return (this->m_dense.end());
		}

		void	insert(T value)
		{
			if (this->m_sparse.size() <= value)
				this->m_sparse.resize(value + 1, INVALID_ID);

			assert(("Value already exists", this->m_sparse[value] == INVALID_ID));

			this->m_dense.push_back(value);
			this->m_sparse[value] = this->m_dense.size() - 1;
		}
		void	erase(T value)
		{
			assert(("Value does not exist", this->m_sparse[value] != INVALID_ID));

			size_t id = this->m_sparse[value];

			std::iter_swap(this->m_dense.begin() + this->m_sparse[value], this->m_dense.end() - 1);
			this->m_sparse[this->m_dense[id]] = id;
			this->m_sparse[value] = INVALID_ID;
			this->m_dense.pop_back();
		}

		T	*data()
		{
			return (this->m_dense.data());
		}
		size_t	size() const
		{
			return (this->m_dense.size());
		}
	};
}
