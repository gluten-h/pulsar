#pragma once

#include "gfx/gfx.h"


namespace pulsar
{
	class transform;

	class shadow_map
	{
	protected:
		UINT m_slot = 0u;

		shadow_map &operator=(const shadow_map&) = delete;
		shadow_map &operator=(shadow_map&&) = delete;
		shadow_map(const shadow_map&) = delete;
		shadow_map(shadow_map&&) = delete;
		shadow_map() = default;
		virtual ~shadow_map() = default;

	public:
		void	set_slot(UINT slot);

		virtual void	clear() = 0;
		virtual uint8_t	draw_calls() const = 0;

		virtual void	bind_rtv(uint8_t id, const pulsar::transform *transform) = 0;
		virtual void	bind_srv() = 0;

		virtual void	unbind_rtv() = 0;
		virtual void	unbind_srv() = 0;

		virtual void	set(UINT width, UINT height, float z_near = 0.001f, float z_far = 1000.0f){ }
	};
}
