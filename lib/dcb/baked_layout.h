#pragma once

#include "raw_layout.h"


namespace pulsar
{
	namespace dcb
	{
		class baked_layout : public pulsar::dcb::layout
		{
		private:
			friend class buffer;

		private:
			std::shared_ptr<pulsar::dcb::layout_elem>	yield_root();
			std::shared_ptr<pulsar::dcb::layout_elem>	share_root() const;

			size_t	size() const noexcept;

		public:
			baked_layout() = delete;
			baked_layout(pulsar::dcb::raw_layout &&raw_layout);
			baked_layout(pulsar::dcb::raw_layout &raw_layout);

			const pulsar::dcb::layout_elem	&operator[](const std::string &key) const;
		};
	}
}
