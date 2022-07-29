#pragma once

#include "buffer_resource.h"
#include "dcb/dcb.h"


namespace pulsar
{
	class dynamic_cbuffer : public pulsar::buffer_resource
	{
	protected:
		pulsar::dcb::buffer	*mp_dcb = NULL;
		UINT m_slot = 0u;

	private:
		void	create_dcb(pulsar::dcb::buffer *buffer);

	protected:
		dynamic_cbuffer &operator=(const dynamic_cbuffer&) = delete;
		dynamic_cbuffer &operator=(dynamic_cbuffer&&) = delete;
		dynamic_cbuffer(const dynamic_cbuffer&) = delete;
		dynamic_cbuffer(dynamic_cbuffer&&) = delete;
		dynamic_cbuffer() = default;
		dynamic_cbuffer(pulsar::dcb::buffer *buffer, UINT slot = 0u);
		virtual ~dynamic_cbuffer() = default;

	public:
		bool	is_modified() const;
		void	update();

		void	set(pulsar::dcb::buffer *buffer);
		void	set_slot(UINT slot);
	};
}
