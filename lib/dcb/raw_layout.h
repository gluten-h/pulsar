#pragma once

#include "layout.h"


namespace pulsar
{
	namespace dcb
	{
		class raw_layout : public pulsar::dcb::layout
		{
		private:
			friend class baked_layout;

		private:
			std::shared_ptr<pulsar::dcb::layout_elem>	yield_finalize_root();
			std::shared_ptr<pulsar::dcb::layout_elem>	share_finalize_root();

		public:
			raw_layout();

			pulsar::dcb::layout_elem	&operator[](const std::string &key);
			pulsar::dcb::layout_elem	&add(pulsar::dcb::TYPE type, const std::string &key);

			template<pulsar::dcb::TYPE type>
			pulsar::dcb::layout_elem	&add(const std::string &key)
			{
				return (this->m_root->add<type>(key));
			}
		};
	}
}
