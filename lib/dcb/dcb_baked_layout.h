#pragma once

#include "dcb_raw_layout.h"


namespace PULSAR
{
	namespace DCB
	{
		class baked_layout : public PULSAR::DCB::layout
		{
		private:
			friend class buffer;

		public:
			baked_layout() = delete;
			baked_layout(PULSAR::DCB::raw_layout &&raw_layout) : PULSAR::DCB::layout(raw_layout.yield_finalize_root())
			{

			}
			baked_layout(PULSAR::DCB::raw_layout &raw_layout) : PULSAR::DCB::layout(raw_layout.share_finalize_root())
			{

			}

			const PULSAR::DCB::layout_elem	&operator[](const std::string &key) const
			{
				return const_cast<const layout_elem&>(*this->m_root)[key];
			}

		private:
			std::shared_ptr<PULSAR::DCB::layout_elem>	yield_root()
			{
				return (std::move(this->m_root));
			}

			std::shared_ptr<PULSAR::DCB::layout_elem>	share_root() const
			{
				return (this->m_root);
			}

			size_t	size() const noexcept
			{
				return (this->m_root->size());
			}
		};
	}
}
