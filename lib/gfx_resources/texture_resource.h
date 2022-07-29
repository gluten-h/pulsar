#pragma once

#include "gfx/gfx.h"


namespace pulsar
{
	class texture_resource
	{
	protected:
		ID3D11Texture2D *mp_texture = NULL;

		void	create_texture(D3D11_TEXTURE2D_DESC &td);
		void	destroy_texture();

	public:
		texture_resource &operator=(const texture_resource&) = delete;
		texture_resource &operator=(texture_resource&&) = delete;
		texture_resource(const texture_resource&) = delete;
		texture_resource(texture_resource&&) = delete;
		texture_resource() = default;
		virtual ~texture_resource();

		ID3D11Texture2D		*texture();
		XMUINT2		size() const;
	};
}
