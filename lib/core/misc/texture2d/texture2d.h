#pragma once

#include "unclassified.h"
#include "pulsar_exc.h"


namespace PULSAR
{
	class TEXTURE2D : public PULSAR::unclassified
	{
	private:
		ID3D11Texture2D		*texture = NULL;


		void	set_texture_memory(float width, float height, DXGI_FORMAT format, UINT bind_flags, UINT cpu_access_flags);
		void	remove_texture_memory();

		void	copy_assign(const TEXTURE2D &t);

	public:
		TEXTURE2D	&operator=(const TEXTURE2D &t);
		TEXTURE2D(const TEXTURE2D &t);
		TEXTURE2D();
		TEXTURE2D(float width, float height, DXGI_FORMAT format, UINT bind_flags = 0u, UINT cpu_access_flags = 0u);
		~TEXTURE2D();

		void	set_texture(float width, float height, DXGI_FORMAT format, UINT bind_flags = 0u, UINT cpu_access_flags = 0u);

		ID3D11Texture2D *get_texture()
		{
			return (this->texture);
		}
	};
}
