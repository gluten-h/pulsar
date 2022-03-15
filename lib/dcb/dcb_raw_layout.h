#pragma once

#include "dcb_layout.h"


namespace PULSAR
{
	namespace DCB
	{
		class raw_layout : public PULSAR::DCB::layout
		{
		private:
			friend class baked_layout;

		public:
			raw_layout() : PULSAR::DCB::layout(std::shared_ptr<PULSAR::DCB::layout_elem>(new PULSAR::DCB::layout_elem(PULSAR::DCB::Struct)))
			{

			}

			PULSAR::DCB::layout_elem	&operator[](const std::string &key)
			{
				return (*this->m_root)[key];
			}


			PULSAR::DCB::layout_elem	&add(PULSAR::DCB::TYPE type, const std::string &key)
			{
				return (this->m_root->add(type, key));
			}

			template<PULSAR::DCB::TYPE type>
			PULSAR::DCB::layout_elem	&add(const std::string &key)
			{
				return (this->m_root->add<type>(key));
			}

		private:
			std::shared_ptr<PULSAR::DCB::layout_elem>	yield_finalize_root()
			{
				std::shared_ptr<PULSAR::DCB::layout_elem> root = std::move(this->m_root);
				root->finalize(0ull);
				*this = raw_layout();

				return (root);
			}

			std::shared_ptr<PULSAR::DCB::layout_elem>	share_finalize_root()
			{
				std::shared_ptr<PULSAR::DCB::layout_elem> root = this->m_root;
				root->finalize(0ull);

				return (root);
			}
		};
	}
}
