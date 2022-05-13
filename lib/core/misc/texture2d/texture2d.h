//#pragma once
//
//#include "_gfx/_gfx.h"
//#include "exceptions/pulsar_exc.h"
//
//
//namespace PULSAR
//{
//	class texture2d
//	{
//	private:
//		ID3D11Texture2D *mp_texture = NULL;
//		
//	private:
//		void	create_texture2d(UINT width, UINT height, DXGI_FORMAT format, UINT bind_flags, UINT cpu_access_flags);
//		void	free();
//
//		void	copy_assign(const texture2d &t);
//
//	public:
//		texture2d	&operator=(const texture2d &t);
//		texture2d(const texture2d &t);
//		texture2d();
//		texture2d(UINT width, UINT height, DXGI_FORMAT format, UINT bind_flags = 0u, UINT cpu_access_flags = 0u);
//		~texture2d();
//
//		void	set(UINT width, UINT height, DXGI_FORMAT format, UINT bind_flags = 0u, UINT cpu_access_flags = 0u);
//		ID3D11Texture2D		*get();
//	};
//}
