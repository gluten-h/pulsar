#pragma once

#include "layout_elem.h"
#include <memory>


namespace PULSAR
{
	namespace dcb
	{
		class layout
		{
		protected:
			std::shared_ptr<PULSAR::dcb::layout_elem>	m_root;

		protected:
			layout(std::shared_ptr<PULSAR::dcb::layout_elem> root)
			{
				this->m_root = std::move(root);
			}

		public:
			layout() = delete;
		};
	}
}
