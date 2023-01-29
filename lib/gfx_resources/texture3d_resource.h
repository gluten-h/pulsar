#pragma once

#include "gfx/gfx.h"


namespace pulsar
{
	class texture3d_resource
	{
	protected:
		ID3D11Texture3D *mp_texture = NULL;

		void	create_texture(D3D11_TEXTURE3D_DESC *td, const D3D11_SUBRESOURCE_DATA *subresource_data);
		void	destroy_texture();

	public:
		texture3d_resource &operator=(const texture3d_resource&) = delete;
		texture3d_resource &operator=(texture3d_resource&&) = delete;
		texture3d_resource(const texture3d_resource&) = delete;
		texture3d_resource(texture3d_resource&&) = delete;
		texture3d_resource() = default;
		virtual ~texture3d_resource();

		ID3D11Texture3D		*texture();
		XMUINT3		size() const;
	};
}
