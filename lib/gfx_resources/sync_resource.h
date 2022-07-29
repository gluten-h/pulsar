#pragma once

#include "gfx/gfx.h"
#include <vector>


namespace pulsar
{
	class sync_resource
	{
	private:
		std::vector<sync_resource*> m_linked_resources;

		void	resize_linked(UINT width, UINT height);

	protected:
		virtual void	resize_resource(UINT width, UINT height){ }

	public:
		sync_resource() = default;
		virtual ~sync_resource() = default;

		void	link(sync_resource *resource);
		void	unlink(sync_resource *resource);

		void	resize(UINT width, UINT height)
		{
			this->resize_resource(width, height);
			this->resize_linked(width, height);
		}
	};
}
