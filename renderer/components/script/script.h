#pragma once

namespace pulsar
{
	class script
	{
	protected:
		script() = default;
		virtual ~script() = default;

	public:
		virtual void	execute(float delta_time) = 0;
	};
}
