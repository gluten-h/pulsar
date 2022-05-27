#pragma once

#include "bindable/bindable.h"


namespace pulsar
{
	class sampler : public pulsar::bindable
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
		sampler(UINT slot);
		~sampler();

		void	set_slot(UINT slot);

		void	bind() const;
		void	unbind() const;
	};
}
