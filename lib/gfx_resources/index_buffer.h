#pragma once

#include "buffer_resource.h"


namespace pulsar
{
	class index_buffer : public pulsar::buffer_resource
	{
	private:
		void	create_index_buffer(const void *data, UINT size);

	public:
		index_buffer &operator=(const index_buffer&) = delete;
		index_buffer &operator=(index_buffer&&) = delete;
		index_buffer(const index_buffer&) = delete;
		index_buffer(index_buffer&&) = delete;
		index_buffer() = default;
		index_buffer(const void *data, UINT size);
		~index_buffer() = default;

		void	set(const void *data, UINT size);
	};
}
