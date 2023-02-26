#pragma once

#include "gfx/gfx.h"


namespace pulsar
{
	class texture2d_resource
	{
	protected:
		ID3D11Texture2D *mp_texture = NULL;

		void	create_texture(D3D11_TEXTURE2D_DESC *td);
		void	destroy_texture();

	public:
		texture2d_resource &operator=(const texture2d_resource&) = delete;
		texture2d_resource &operator=(texture2d_resource&&) = delete;
		texture2d_resource(const texture2d_resource&) = delete;
		texture2d_resource(texture2d_resource&&) = delete;
		texture2d_resource() = default;
		virtual ~texture2d_resource();

		ID3D11Texture2D		*texture();
		XMUINT2		size() const;
	};
}
