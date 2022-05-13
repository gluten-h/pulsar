#pragma once

#include "_gfx/_gfx.h"
#include <vector>


namespace PULSAR
{
	class buffer_resource
	{
	private:
		std::vector<buffer_resource*> m_linked_buffer_resources;

	protected:
		void	resize_linked(UINT width, UINT height);
		void	clear_linked();

	public:
		void	link_buffer_resource(buffer_resource *p_buffer_resource)
		{
			this->m_linked_buffer_resources.push_back(p_buffer_resource);
		}

		virtual void	resize(UINT width, UINT height) = 0;
		virtual void	clear() = 0;
	};
}
