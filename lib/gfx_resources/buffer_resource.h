#pragma once

#include "gfx/gfx.h"


namespace pulsar
{
	class buffer_resource
	{
	protected:
		ID3D11Buffer *mp_buffer = NULL;

		void	create_buffer(const D3D11_BUFFER_DESC *bd, const D3D11_SUBRESOURCE_DATA *sd);
		void	destroy_buffer();

	public:
		buffer_resource &operator=(const buffer_resource&) = delete;
		buffer_resource &operator=(buffer_resource&&) = delete;
		buffer_resource(const buffer_resource&) = delete;
		buffer_resource(buffer_resource&&) = delete;
		buffer_resource() = default;
		virtual ~buffer_resource();

		ID3D11Buffer	*buffer();
	};
}
