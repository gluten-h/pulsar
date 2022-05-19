#pragma once

#include "gfx/gfx.h"


namespace PULSAR
{
	class bindable
	{
	public:
		virtual void	bind() const{ }
		virtual void	unbind() const{ }
	};
}
