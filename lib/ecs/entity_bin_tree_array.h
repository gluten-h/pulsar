#pragma once

#include <vector>
#include <bitset>

#include "ecs/types.h"


namespace PULSAR
{
	namespace ecs
	{
		template <size_t BIT_SIZE>
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
			entity_bin_tree_array()
			{
				this->m_root = new tree_node;
			}
			~entity_bin_tree_array()
			{
				tree_node *curr_node = this->m_root;
				while (curr_node)
				{
					if (curr_node->left)
					{
						curr_node = curr_node->left;
					}
					else if (curr_node->right)
					{
						curr_node = curr_node->right;
					}
					else
					{
						tree_node *parent_node = curr_node->parent;

						if (curr_node->parent)
						{
							if (parent_node->left == curr_node)
								parent_node->left = NULL;
							else
								parent_node->right = NULL;
							delete curr_node;
						}
						else
						{
							delete this->m_root;
							this->m_root = NULL;
						}

						curr_node = parent_node;
					}
				}
			}

			void	specify_path(const std::bitset<BIT_SIZE> &signature, const PULSAR::ecs::entity &value)
			{
				tree_node *curr_node = this->m_root;
				size_t offset = 0ull;

				size_t bit_count = signature.count();
				size_t i = 0ull;
				while (i < signature.size() && bit_count)
				{
					curr_node->m_children_size++;
					offset += curr_node->m_size + curr_node->m_offset;

					bool bit = signature.test(i);
					if (bit)
					{
						bit_count--;

						if (!curr_node->right)
						{
							curr_node->right = new tree_node;
							curr_node->right->parent = curr_node;
						}
						curr_node = curr_node->right;
					}
					else
					{
						if (!curr_node->right)
						{
							curr_node->right = new tree_node;
							curr_node->right->parent = curr_node;
						}
						curr_node->right->m_offset++;

						if (!curr_node->left)
						{
							curr_node->left = new tree_node;
							curr_node->left->parent = curr_node;
						}
						curr_node = curr_node->left;
					}

					i++;
				}
				offset += curr_node->m_offset;

				curr_node->m_size++;
				this->m_data.insert(this->m_data.begin() + offset, value);
			}

			void	erase(const std::bitset<BIT_SIZE> &signature, const PULSAR::ecs::entity &value)
			{
				tree_node *curr_node = this->m_root;
				size_t offset = 0ull;

				size_t bit_count = signature.count();
				size_t i = 0ull;
				while (i < signature.size() && bit_count)
				{
					curr_node->m_children_size--;
					offset += curr_node->m_size + curr_node->m_offset;

					bool bit = signature.test(i);
					if (bit)
					{
						bit_count--;
						curr_node = curr_node->right;
					}
					else
					{
						if (curr_node->right)
							curr_node->right->m_offset--;

						curr_node = curr_node->left;
					}

					i++;
				}
				offset += curr_node->m_offset;

				auto begin = this->m_data.begin() + offset;
				auto end = (offset + curr_node->m_size + 1 < this->m_data.size()) ? (this->m_data.begin() + offset + curr_node->m_size + 1) : this->m_data.end();

				this->m_data.erase(std::find(begin, end, value));	// maybe add hash map to each tree node to avoid linear search
				curr_node->m_size--;
			}

			const PULSAR::ecs::group	group(const std::bitset<BIT_SIZE> &signature)
			{
				tree_node *curr_node = this->m_root;
				size_t offset = 0ull;

				size_t bit_count = signature.count();
				size_t i = 0ull;
				if (!signature.test(0ull))
				{
					offset += curr_node->m_size;

					if (!curr_node->right)
						return (PULSAR::ecs::group());
					curr_node = curr_node->right;
					i = 1ull;
				}
				while (i < signature.size() && bit_count)
				{
					offset += curr_node->m_size + curr_node->m_offset;

					bool bit = signature.test(i);
					if (bit)
					{
						bit_count--;

						if (!curr_node->right)
							return (PULSAR::ecs::group());
						curr_node = curr_node->right;
					}
					else
					{
						if (!curr_node->left)
							return (PULSAR::ecs::group());
						curr_node = curr_node->left;
					}

					i++;
				}
				offset += curr_node->m_offset;

				return (PULSAR::ecs::group(&this->m_data[offset], curr_node->m_size + curr_node->m_children_size));
			}
		};
	}
}
