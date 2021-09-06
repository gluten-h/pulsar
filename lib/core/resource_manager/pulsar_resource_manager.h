#pragma once

#include <vector>


namespace PULSAR
{
	typedef void (*TERMINATE_DEF)(void);


	class RESOURCE_MANAGER
	{
	private:
		static std::vector<PULSAR::TERMINATE_DEF>	terminate_func;

	public:
		static void		add_terminate(PULSAR::TERMINATE_DEF terminate)
		{
			PULSAR::RESOURCE_MANAGER::terminate_func.push_back(terminate);
		}

		static void		terminate()
		{
			for (auto it = PULSAR::RESOURCE_MANAGER::terminate_func.rbegin(); it != PULSAR::RESOURCE_MANAGER::terminate_func.rend(); it++)
				(*it)();
		}
	};
}
