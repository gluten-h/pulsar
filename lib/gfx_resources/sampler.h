#pragma once

#include "gfx/gfx.h"


namespace pulsar
{
	class sampler
	{
	private:
		ID3D11SamplerState *mp_sampler = NULL;
		UINT m_slot = 0u;

		void	create_sampler(D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE address_mode);
		void	destroy_sampler();

	public:
		sampler &operator=(const sampler&) = delete;
		sampler &operator=(sampler&&) = delete;
		sampler(const sampler&) = delete;
		sampler(sampler&&) = delete;
		sampler() = delete;
		sampler(UINT slot);
		sampler(D3D11_FILTER filter = D3D11_FILTER_ANISOTROPIC, D3D11_TEXTURE_ADDRESS_MODE address_mode = D3D11_TEXTURE_ADDRESS_WRAP, UINT slot = 0u);
		~sampler();

		void	set(D3D11_FILTER filter = D3D11_FILTER_ANISOTROPIC, D3D11_TEXTURE_ADDRESS_MODE address_mode = D3D11_TEXTURE_ADDRESS_WRAP);
		void	set_slot(UINT slot);

		void	bind() const;
		void	unbind() const;
	};
}
