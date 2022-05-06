#pragma once

#include "_gfx/_gfx.h"


namespace PULSAR
{
	class bindable
	{
	public:
		virtual void	bind() const{ }
		virtual void	unbind() const{ }
	};
}
