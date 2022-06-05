#pragma once

#include "node/node.h"


namespace pulsar
{
	class script
	{
	protected:
		pulsar::node *mp_node = NULL;
		
		script(pulsar::node *node)
		{
			this->mp_node = node;
		}

	public:
		script() = delete;
		virtual ~script() = default;

		virtual void	execute(float delta_time) = 0;
	};
}
