#pragma once

#include "bindable/bindable.h"
#include "dcb/buffer.h"


namespace PULSAR
{
	class dynamic_const_buffer : public PULSAR::bindable
	{
	protected:
		ID3D11Buffer *mp_buffer = NULL;
		PULSAR::dcb::buffer	*mp_dcb_buffer = NULL;
		UINT m_slot = 0u;

	private:
		void	create_buffer(PULSAR::dcb::buffer *dcb_buffer);
		void	free();

	public:
		dynamic_const_buffer &operator=(const dynamic_const_buffer&) = delete;
		dynamic_const_buffer &operator=(dynamic_const_buffer&&) = delete;
		dynamic_const_buffer(const dynamic_const_buffer&) = delete;
		dynamic_const_buffer(dynamic_const_buffer&&) = delete;
		dynamic_const_buffer() = default;
		dynamic_const_buffer(UINT slot = 0u);
		dynamic_const_buffer(PULSAR::dcb::buffer *dcb_buffer, UINT slot = 0u);
		~dynamic_const_buffer();

		bool	is_modified() const noexcept;
		void	update();

		void	set_dcb_buffer(PULSAR::dcb::buffer *dcb_buffer);
		void	set_slot(UINT slot);
	};
}
