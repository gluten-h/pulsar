#pragma once

#include "layout.h"


namespace PULSAR
{
	namespace dcb
	{
		class raw_layout : public PULSAR::dcb::layout
		{
		private:
			friend class baked_layout;

		private:
			std::shared_ptr<PULSAR::dcb::layout_elem>	yield_finalize_root();
			std::shared_ptr<PULSAR::dcb::layout_elem>	share_finalize_root();

		public:
			raw_layout();

			PULSAR::dcb::layout_elem	&operator[](const std::string &key);
			PULSAR::dcb::layout_elem	&add(PULSAR::dcb::TYPE type, const std::string &key);

			template<PULSAR::dcb::TYPE type>
			PULSAR::dcb::layout_elem	&add(const std::string &key)
			{
				return (this->m_root->add<type>(key));
			}
		};
	}
}
