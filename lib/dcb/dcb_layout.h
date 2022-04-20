#pragma once

#include "dcb/dcb_layout_elem.h"

#include <memory>
#include <string>


namespace PULSAR
{
	namespace dcb
	{
		class layout
		{
		protected:
			std::shared_ptr<PULSAR::dcb::layout_elem>	m_root;

		public:
			layout() = delete;

		protected:
			layout(std::shared_ptr<PULSAR::dcb::layout_elem> root)
			{
				this->m_root = std::move(root);
			}
		};
	}
}
