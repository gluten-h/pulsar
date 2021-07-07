#pragma once

#include <cstddef>
#include <algorithm>


template <typename T, size_t MAX_SIZE>
struct					grng_ipiston
{
	typedef struct		grng_ipiston_data
	{
		T				*data = NULL;
		int				global_id = -1;
	}					GRNG_ISPISTON_DATA;

	GRNG_ISPISTON_DATA	data[MAX_SIZE];
	int					size = 0;
};

template <typename T, size_t MAX_SIZE>
using GRNG_IPISTON = grng_ipiston<T, MAX_SIZE>;


template <typename T, size_t MAX_SIZE>
class grng_piston
{
public:
	typedef struct					grng_piston_data
	{
		T							data;
		int							interface_id = -1;
	}								GRNG_PISTON_DATA;

private:
	GRNG_PISTON_DATA				data[MAX_SIZE];
	int								data_iter = 0;
	GRNG_IPISTON<T, MAX_SIZE>		ipiston;


	void		rearrange_data(int id)
	{
		int interface_id = this->data[id].interface_id;
		this->data[this->ipiston.data[this->ipiston.size - 1].global_id].interface_id = interface_id;
		this->ipiston.data[interface_id].data = NULL;
		this->ipiston.data[interface_id].global_id = -1;
		std::swap(this->ipiston.data[interface_id], this->ipiston.data[this->ipiston.size - 1]);
	}

	void		remove_data(int id)
	{
		this->rearrange_data(id);

		this->data[id].interface_id = -1;
		this->ipiston.size--;
		this->data_iter = id;
	}


	void		move_data_iter()
	{
		if (this->data_iter >= MAX_SIZE || this->data[this->data_iter].interface_id >= 0)
		{
			int i = -1;
			while (++i < MAX_SIZE)
			{
				if (this->data[i].interface_id == -1)
				{
					this->data_iter = i;
					break;
				}
			}
		}
	}

public:
	grng_piston()
	{
		int i = -1;
		while (++i < MAX_SIZE)
		{
			this->data[i].interface_id = -1;
			this->ipiston.data[i].data = NULL;
			this->ipiston.data[i].global_id = -1;
		}
	}

	~grng_piston() { }


	int						add(const T &value)
	{
		if (this->ipiston.size >= MAX_SIZE)
			return (-1);

		this->move_data_iter();

		int global_id = this->data_iter;
		int interface_id = this->ipiston.size;

		this->data[global_id].data = value;
		this->data[global_id].interface_id = interface_id;
		this->ipiston.data[interface_id].data = &this->data[global_id].data;
		this->ipiston.data[interface_id].global_id = global_id;

		this->data_iter++;
		this->ipiston.size++;

		return (global_id);
	}

	void					remove(unsigned int id)
	{
		this->remove_data(id);
	}

	void					remove_secure(unsigned int id)
	{
		if (id >= MAX_SIZE || this->data[id].interface_id == -1)
			return;

		this->remove_data(id);
	}

	void					set(unsigned int id, const T &value)
	{
		this->data[id].data = value;
	}

	void					set_secure(unsigned int id, const T &value)
	{
		if (id >= MAX_SIZE || this->data[id].interface_id == -1)
			return;
		this->data[id].data = value;
	}

	T						*get_secure(unsigned int id)
	{
		if (id >= MAX_SIZE || this->data[id].interface_id == -1)
			return (NULL);
		return (&this->data[id].data);
	}

	T						*get(unsigned int id)
	{
		return (&this->data[id].data);
	}

	int						next_id()
	{
		if (this->ipiston.size >= MAX_SIZE)
			return (-1);

		this->move_data_iter();

		return (this->data_iter);
	}


	const GRNG_IPISTON<T, MAX_SIZE>		*get_ipiston() const
	{
		return (&this->ipiston);
	}
};


template <typename T, size_t MAX_SIZE>
using GRNG_PISTON = grng_piston<T, MAX_SIZE>;
