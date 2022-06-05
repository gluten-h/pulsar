#pragma once

#include "gfx/gfx.h"
#include <vector>


namespace pulsar
{
	class buffer_resource
	{
	private:
		std::vector<buffer_resource*> m_linked_buffer_resources;

	protected:
		void	resize_linked(UINT width, UINT height);
		void	clear_linked();

	public:
		void	link_buffer_resource(buffer_resource *buffer_resource)
		{
			this->m_linked_buffer_resources.push_back(buffer_resource);
		}
		void	unlink_buffer_resource(buffer_resource *buffer_resource)
		{
			auto it = std::find(this->m_linked_buffer_resources.begin(), this->m_linked_buffer_resources.end(), buffer_resource);
			if (it == this->m_linked_buffer_resources.end())
				return;

			this->m_linked_buffer_resources.erase(it);
		}

		virtual void	resize(UINT width, UINT height) = 0;
		virtual void	clear() = 0;
	};
}
