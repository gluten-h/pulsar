#pragma once

#include "dcb/dcb_layout.h"


namespace PULSAR
{
	namespace dcb
	{
		class raw_layout : public PULSAR::dcb::layout
		{
		private:
			friend class baked_layout;

		public:
			raw_layout() : PULSAR::dcb::layout(std::shared_ptr<PULSAR::dcb::layout_elem>(new PULSAR::dcb::layout_elem(PULSAR::dcb::Struct)))
			{

			}

			PULSAR::dcb::layout_elem	&operator[](const std::string &key)
			{
				return (*this->m_root)[key];
			}


			PULSAR::dcb::layout_elem	&add(PULSAR::dcb::TYPE type, const std::string &key)
			{
				return (this->m_root->add(type, key));
			}

			template<PULSAR::dcb::TYPE type>
			PULSAR::dcb::layout_elem	&add(const std::string &key)
			{
				return (this->m_root->add<type>(key));
			}

		private:
			std::shared_ptr<PULSAR::dcb::layout_elem>	yield_finalize_root()
			{
				std::shared_ptr<PULSAR::dcb::layout_elem> root = std::move(this->m_root);
				root->finalize(0ull);
				*this = raw_layout();

				return (root);
			}

			std::shared_ptr<PULSAR::dcb::layout_elem>	share_finalize_root()
			{
				std::shared_ptr<PULSAR::dcb::layout_elem> root = this->m_root;
				root->finalize(0ull);

				return (root);
			}
		};
	}
}
