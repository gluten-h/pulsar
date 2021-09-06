#pragma once

#include "piston.h"
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
		PULSAR::PISTON<T*, MAX_SIZE>			data;
		const PULSAR::IPISTON<T*, MAX_SIZE>		*idata = this->data.get_ipiston();
		std::unordered_map<T*, int>				data_id_map;


		virtual void	add_event(int added_id, T *data){ }
		virtual void	remove_event(int removed_id, T *data){ }

		bool	is_exists(T *data)
		{
			try
			{
				this->data_id_map.at(data);
				return (true);
			}
			catch (const std::out_of_range &ex)
			{
				return (false);
			}
		}
		bool	is_exists(int id)
		{
			return (this->data.get_secure(id) != NULL);
		}

		bool	is_available(T *data)
		{
			return (!is_exists(data) && this->idata->size < MAX_SIZE);
		}


		int 	add_manager(T *data)
		{
			int id = this->data.add(data);
			this->data_id_map[data] = id;
			this->add_event(id, data);

			return (id);
		}

		void	remove_manager(T *data)
		{
			int id = this->data_id_map.at(data);

			this->data_id_map.erase(data);
			this->data.remove(id);
			this->remove_event(id, data);
		}

	public:
		MANAGER(){ }

		void		remove_secure(T *data)
		{
			if (!this->is_exists(data))
				return;

			this->remove_manager(data);
		}

		void		remove(T *data)
		{
			this->remove_manager(data);
		}

		void		remove_secure(unsigned int id)
		{
			if (!this->is_exists(id))
				return;

			this->remove_manager(*this->data.get(id));
		}

		void		remove(unsigned int id)
		{
			this->remove_manager(*this->data.get(id));
		}


		T	*get_data_secure(unsigned int id)
		{
			T **data_ptr = this->data.get_secure(id);
			if (!data_ptr)
				return (NULL);

			return (*data_ptr);
		}

		T	*get_data(unsigned int id)
		{
			return (*this->data.get(id));
		}

		const PULSAR::IPISTON<T*, MAX_SIZE> *get_idata() const
		{
			return (this->idata);
		}
	};
}
