#pragma once

#include "gfx_resources/texture3d_resource.h"
#include <vector>


namespace pulsar
{
	class shadow_filter : public pulsar::texture3d_resource
	{
	private:
		ID3D11ShaderResourceView *mp_srv = NULL;
		std::vector<float> m_data;
		UINT m_slot;

	public:
		shadow_filter &operator=(const shadow_filter&) = delete;
		shadow_filter &operator=(shadow_filter&&) = delete;
		shadow_filter(const shadow_filter &st) = delete;
		shadow_filter(shadow_filter&&) = delete;
		shadow_filter() = delete;
		shadow_filter(UINT window_size, UINT filter_size, UINT slot = 0u);
		~shadow_filter();

		void	set_slot(UINT slot);

		void	bind() const;
		void	unbind() const;
	};
}
