#pragma once

#include "bindable/bindable.h"


namespace PULSAR
{
	class sampler : public PULSAR::bindable
	{
	private:
		ID3D11SamplerState *mp_sampler = NULL;
		UINT m_slot = 0u;

	private:
		void	create_sampler();
		void	free();

	public:
		sampler &operator=(const sampler&) = delete;
		sampler &operator=(sampler&&) = delete;
		sampler(const sampler&) = delete;
		sampler(sampler&&) = delete;
		sampler();
		sampler(UINT slot = 0u);
		~sampler();

		void	set_slot(UINT slot);

		void	bind() const override;
		void	unbind() const override;
	};
}
