#pragma once

#include "grng_id3d.h"
#include "grng_exc_macros.h"


class grng_texture2d : public GRNG_ID3D
{
private:
	ID3D11Texture2D		*texture = NULL;


	void				set_texture_memory(float width, float height, DXGI_FORMAT format, UINT bind_flags, UINT cpu_access_flags);
	void				remove_texture_memory();

	void				copy_assign(const grng_texture2d &t);

public:
	grng_texture2d		&operator=(const grng_texture2d &t);
	grng_texture2d(const grng_texture2d &t);
	grng_texture2d();
	grng_texture2d(float width, float height, DXGI_FORMAT format, UINT bind_flags = 0u, UINT cpu_access_flags = 0u);
	~grng_texture2d();

	void				set_texture(float width, float height, DXGI_FORMAT format, UINT bind_flags = 0u, UINT cpu_access_flags = 0u);

	ID3D11Texture2D		*get_texture()
	{
		return (this->texture);
	}
};

using GRNG_TEXTURE2D = grng_texture2d;
