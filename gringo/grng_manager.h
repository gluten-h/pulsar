#pragma once

#include "grng_piston.h"
#include "grng_utils.h"

#include <unordered_map>
#include <stdexcept>
#include <string>


template <typename T, size_t MAX_SIZE>
class grng_manager
{
protected:
	GRNG_PISTON<T*, MAX_SIZE>				data;
	const GRNG_IPISTON<T*, MAX_SIZE>		*idata = this->data.get_ipiston();
	std::unordered_map<T*, int>				data_id_map;


	virtual void		add_event(int added_id, T &data) = 0;
	virtual void		remove_event(int removed_id, T &data) = 0;


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

	bool	is_available()
	{
		return (this->idata->size < MAX_SIZE);
	}


	T		*add_manager(T *data)
	{
		int id = this->data.add(data);
		this->data_id_map[data] = id;
		this->add_event(id, *data);

		return (data);
	}

	void	remove_manager(T *data)
	{
		int id = this->data_id_map.at(data);

		this->data_id_map.erase(data);
		this->data.remove(id);
		this->remove_event(id, *data);

		delete data;
	}

public:
	grng_manager(){ }
	~grng_manager()
	{
		for (auto &it : this->data_id_map)
			delete it.first;
		this->data_id_map.clear();
	}

	void		remove_secure(T &data)
	{
		if (!this->is_exists(&data))
			return;

		this->remove_manager(&data);
	}

	void		remove(T &data)
	{
		this->remove_manager(&data);
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


	T			*get_data_secure(unsigned int id)
	{
		T **data_ptr = this->data.get_secure(id);
		if (!data_ptr)
			return (NULL);

		return (*data_ptr);
	}

	T			*get_data(unsigned int id)
	{
		return (*this->data.get(id));
	}
};

template <typename T, size_t MAX_SIZE>
using GRNG_MANAGER = grng_manager<T, MAX_SIZE>;
