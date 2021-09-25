#pragma once

#include "fixed_vector.h"
#include "pulsar_utils.h"

#include <unordered_map>
#include <stdexcept>
#include <string>


namespace PULSAR
{
	template <typename T, size_t MAX_SIZE>
	class MANAGER
	{
	protected:
		PULSAR::FIXED_VECTOR<T*, MAX_SIZE>	data;
		std::unordered_map<T*, int>			data_id_map;


		virtual void	add_event(int added_id, T *value){ }
		virtual void	remove_event(int removed_id, T *value){ }

		bool	is_exists(T *value)
		{
			try
			{
				this->data_id_map.at(value);
				return (true);
			}
			catch (const std::out_of_range &ex)
			{
				return (false);
			}
		}
		bool	is_exists(int id)
		{
			//return (this->data.get_secure(id) != NULL);

			try
			{
				this->data.at(id);
				return (true);
			}
			catch (const std::out_of_range &exc)
			{
				return (false);
			}
		}
		bool	is_available(T *value)
		{
			//return (!is_exists(value) && this->idata->size < MAX_SIZE);

			return (!this->is_exists(value) && this->data.size() < MAX_SIZE);
		}

		int 	add_manager(T *value)
		{
			int id = this->data.add(value);
			this->data_id_map[value] = id;
			this->add_event(id, value);

			return (id);
		}
		void	remove_manager(T *value)
		{
			int id = this->data_id_map.at(value);
			
			this->data_id_map.erase(value);
			this->data.remove(id);
			this->remove_event(id, value);
		}

	public:
		MANAGER(){ }
		
		typename FIXED_VECTOR<T*, MAX_SIZE>::iterator	begin()
		{
			return (this->data.begin());
		}
		typename FIXED_VECTOR<T*, MAX_SIZE>::iterator	end()
		{
			return (this->data.end());
		}
		
		size_t	size() const
		{
			return (this->data.size());
		}

		void	remove(T *value)
		{
			if (!this->is_exists(value))
				return;
			this->remove_manager(value);
		}

		void	remove(unsigned int id)
		{
			if (!this->is_exists(id))
				return;
			this->remove_manager(*this->data.get(id));
		}

		T	*get_elem(unsigned int id)
		{
			try
			{
				T *elem = (T*)&this->data.at(id);
				return (elem);
			}
			catch (const std::out_of_range &exc)
			{
				return (NULL);
			}
		}
	};
}
