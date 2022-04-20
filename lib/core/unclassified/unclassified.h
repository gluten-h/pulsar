#pragma once

#include "pulsar_id3d.h"


namespace PULSAR
{
	class unclassified
	{
	protected:
		static inline PULSAR::id3d	m_id3d;

		IDXGIFactory		*idxgi_factory = unclassified::m_id3d.idxgi_factory();
		ID3D11Device		*device = unclassified::m_id3d.device();
		ID3D11DeviceContext	*device_context = unclassified::m_id3d.device_context();

	private:
		//bool	m_alloc = false;

	public:
		unclassified()
		{
			
		}
		~unclassified()
		{
			// not shure about it
			/*if (!m_alloc)
				return;
			this->m_alloc = false;

			delete this;*/
		}
	};
}
