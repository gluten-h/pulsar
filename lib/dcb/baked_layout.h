#pragma once

#include "dcb/raw_layout.h"


namespace PULSAR
{
	namespace dcb
	{
		class baked_layout : public PULSAR::dcb::layout
		{
		private:
			friend class buffer;

		public:
			baked_layout() = delete;
			baked_layout(PULSAR::dcb::raw_layout &&raw_layout) : PULSAR::dcb::layout(raw_layout.yield_finalize_root())
			{

			}
			baked_layout(PULSAR::dcb::raw_layout &raw_layout) : PULSAR::dcb::layout(raw_layout.share_finalize_root())
			{

			}

			const PULSAR::dcb::layout_elem	&operator[](const std::string &key) const
			{
				return const_cast<const layout_elem&>(*this->m_root)[key];
			}

		private:
			std::shared_ptr<PULSAR::dcb::layout_elem>	yield_root()
			{
				return (std::move(this->m_root));
			}

			std::shared_ptr<PULSAR::dcb::layout_elem>	share_root() const
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
