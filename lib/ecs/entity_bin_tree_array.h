#pragma once

#include <vector>
#include <bitset>

#include "ecs/types.h"


namespace PULSAR
{
	namespace ecs
	{
		class entity_bin_tree_array
		{
		private:
			struct tree_node
			{
				size_t m_offset = 0ull;

				size_t m_size = 0ull;
				size_t m_children_size = 0ull;

				tree_node *parent = NULL;
				tree_node *left = NULL;
				tree_node *right = NULL;
			};

		private:
			std::vector<PULSAR::ecs::entity> m_data;
			tree_node *m_root = NULL;

		public:
			entity_bin_tree_array();
			~entity_bin_tree_array();

			void	specify_path(const std::bitset<PULSAR::ecs::MAX_COMPONENTS_TYPES> &signature, const PULSAR::ecs::entity &value);
			void	erase(const std::bitset<PULSAR::ecs::MAX_COMPONENTS_TYPES> &signature, const PULSAR::ecs::entity &value);
			const PULSAR::ecs::group	group(const std::bitset<PULSAR::ecs::MAX_COMPONENTS_TYPES> &signature);
		};
	}
}
