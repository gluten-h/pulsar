#pragma once

#include "grng_piston.h"

#include <unordered_map>
#include <stdexcept>


template <typename T, size_t MAX_SIZE>
class grng_manager
{
protected:
	GRNG_PISTON<T*, MAX_SIZE>			data;
	const GRNG_IPISTON<T*, MAX_SIZE>	*idata = this->data.get_ipiston();
	std::unordered_map<T*, int>			data_id_map;


	virtual void		add_event(int added_id) = 0;
	virtual void		remove_event(int removed_id) = 0;

private:
	void		remove_data(T &data)
	{
		int id = this->data_id_map.at(&data);
		this->data_id_map.erase(&data);
		this->data.remove_secure(id);
		
		this->remove_event(id);
	}

public:
	grng_manager(){ }
	~grng_manager()
	{
		this->data_id_map.clear();
	}


	int		add(T &data)
	{
		try
		{
			int id = this->data_id_map.at(&data);
			return (-1);
		}
		catch (const std::out_of_range &ex){ }

		if (this->idata->size >= MAX_SIZE)
			return (-1);

		int id = this->data.add(&data);
		this->data_id_map[&data] = id;
		this->add_event(id);

		return (id);
	}

	void		remove_secure(T &data)
	{
		try
		{
			this->data_id_map.at(&data);
			this->remove_data(data);
		}
		catch (const std::out_of_range &ex)
		{
			return;
		}
	}

	void		remove_secure(unsigned int id)
	{
		T **data_ptr = this->data.get_secure(id);
		if (!data_ptr)
			return;
		this->remove_data(**data_ptr);
	}

	void		remove(unsigned int id)
	{
		T **data_ptr = this->data.get(id);
		this->remove_data(**data_ptr);
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
		T **data_ptr = this->data.get(id);
		return (*data_ptr);
	}


	virtual void		bind() = 0;
};

template <typename T, size_t MAX_SIZE>
using GRNG_MANAGER = grng_manager<T, MAX_SIZE>;
