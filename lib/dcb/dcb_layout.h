#pragma once

#include "dcb_layout_elem.h"

#include <memory>
#include <string>


namespace PULSAR
{
	namespace DCB
	{
		class layout
		{
		protected:
			std::shared_ptr<PULSAR::DCB::layout_elem>	m_root;

		public:
			layout() = delete;

		protected:
			layout(std::shared_ptr<PULSAR::DCB::layout_elem> root)
			{
				this->m_root = std::move(root);
			}
		};
	}
}
