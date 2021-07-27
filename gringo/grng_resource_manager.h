#pragma once

#include <vector>


typedef void (*GRNG_TERMINATE_DEF)(void);


class grng_resource_manager
{
private:
	static std::vector<GRNG_TERMINATE_DEF>		terminate_func;

public:
	static void		add_terminate(GRNG_TERMINATE_DEF terminate)
	{
		grng_resource_manager::terminate_func.push_back(terminate);
	}

	static void		terminate()
	{
		for (auto it = grng_resource_manager::terminate_func.rbegin(); it != grng_resource_manager::terminate_func.rend(); it++)
			(*it)();
	}
};

using GRNG_RESOURCE_MANAGER = grng_resource_manager;
