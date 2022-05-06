#pragma once

#include "raw_layout.h"


namespace PULSAR
{
	namespace dcb
	{
		class baked_layout : public PULSAR::dcb::layout
		{
		private:
			friend class buffer;

		private:
			std::shared_ptr<PULSAR::dcb::layout_elem>	yield_root();
			std::shared_ptr<PULSAR::dcb::layout_elem>	share_root() const;

			size_t	size() const noexcept;

		public:
			baked_layout() = delete;
			baked_layout(PULSAR::dcb::raw_layout &&raw_layout);
			baked_layout(PULSAR::dcb::raw_layout &raw_layout);

			const PULSAR::dcb::layout_elem	&operator[](const std::string &key) const;
		};
	}
}
