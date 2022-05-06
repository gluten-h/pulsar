#pragma once

#include "ecs/types.h"
#include "ecs/entity_bin_tree_array.h"
#include "ecs/system.h"

#include <cassert>
#include <bitset>
#include <vector>
#include <unordered_map>
#include <tuple>


namespace PULSAR
{
	namespace ecs
	{
		class registry
		{
		private:
			using signature = std::bitset<MAX_COMPONENTS_TYPES>;

			PULSAR::ecs::entity m_entity_id_iter = 0u;

			std::unordered_map<PULSAR::ecs::entity, signature> m_entities_signatures;
			std::unordered_map<PULSAR::ecs::entity, std::unordered_map<PULSAR::ecs::component_type_id, void *>> m_entities_components;

			PULSAR::ecs::entity_bin_tree_array m_entity_tree;

			std::vector<PULSAR::ecs::system *> m_systems;

		private:
			template<std::size_t I = 0, typename... Tp>
			inline typename std::enable_if<I == sizeof...(Tp), signature>::type		read_type_bits(std::tuple<Tp...> &t)
			{
				return (signature());
			}

			template<std::size_t I = 0, typename... Tp>
			inline typename std::enable_if < I < sizeof...(Tp), signature>::type	read_type_bits(std::tuple<Tp...> &t)
			{
				signature sig;
				sig.set(PULSAR::ecs::component_type::id<decltype(std::get<I>(t))>(), 1);

				sig |= read_type_bits<I + 1, Tp...>(t);

				return (sig);
			}

		public:
			registry() = default;
			~registry() = default;

			registry(const registry &) = delete;
			registry(registry &&) = delete;
			registry &operator=(const registry &) = delete;
			registry &operator=(registry &&) = delete;

			PULSAR::ecs::entity		create()
			{
				PULSAR::ecs::entity entity = this->m_entity_id_iter++;

				signature sig;
				this->m_entities_signatures[entity] = sig;
				this->m_entities_components[entity];

				this->m_entity_tree.specify_path(sig, entity);

				return (entity);
			}

			void	destroy(const PULSAR::ecs::entity entity)
			{
				assert(("Entity id is invalid", this->m_entities_signatures.find(entity) != this->m_entities_signatures.end()));

				signature &sig = this->m_entities_signatures[entity];
				auto &entity_components = this->m_entities_components[entity];

				for (auto &[component_type_id, data] : entity_components)
					delete data;

				this->m_entity_tree.erase(sig, entity);
				this->m_entities_components.erase(entity);
				this->m_entities_signatures.erase(entity);
			}

			// create another 'emplace' function with ability to add multiple components at once
			template <typename T, typename... Args>
			T	&emplace(const PULSAR::ecs::entity entity, Args&&... args)
			{
				const PULSAR::ecs::component_type_id component_type_id = PULSAR::ecs::component_type::id<T>();
				assert(("Component type id overflow", component_type_id < MAX_COMPONENTS_TYPES));
				assert(("Entity id is invalid", this->m_entities_signatures.find(entity) != this->m_entities_signatures.end()));

				signature old_sig = this->m_entities_signatures[entity];
				signature &new_sig = this->m_entities_signatures[entity].set(component_type_id, 1);
				if (old_sig.to_ulong() == new_sig.to_ulong())
				{
					auto &entity_components = this->m_entities_components[entity];

					delete entity_components[component_type_id];
					T *new_component = new T(args...);
					entity_components[component_type_id] = (void *)new_component;

					return (*new_component);
				}
				else
				{
					auto &entity_components = this->m_entities_components[entity];

					T *new_component = new T(args...);
					entity_components[component_type_id] = (void *)new_component;

					this->m_entity_tree.erase(old_sig, entity);
					this->m_entity_tree.specify_path(new_sig, entity);

					return (*new_component);
				}
			}

			template <typename T>
			void	erase(const PULSAR::ecs::entity entity)
			{
				const PULSAR::ecs::component_type_id component_type_id = PULSAR::ecs::component_type::id<T>();
				assert(("Component type id overflow", component_type_id < MAX_COMPONENTS_TYPES));
				assert(("Entity id is invalid", this->m_entities_signatures.find(entity) != this->m_entities_signatures.end()));

				auto &entity_components = this->m_entities_components[entity];
				signature old_sig = this->m_entities_signatures[entity];
				signature &new_sig = this->m_entities_signatures[entity].set(component_type_id, 0);

				delete entity_components[component_type_id];
				entity_components.erase(component_type_id);

				this->m_entity_tree.erase(old_sig, entity);
				this->m_entity_tree.specify_path(new_sig, entity);
			}


			template <typename T>
			bool	has(const PULSAR::ecs::entity entity)
			{
				const PULSAR::ecs::component_type_id component_type_id = PULSAR::ecs::component_type::id<T>();
				assert(("Component type id overflow", component_type_id < MAX_COMPONENTS_TYPES));
				assert(("Entity id is invalid", this->m_entities_signatures.find(entity) != this->m_entities_signatures.end()));

				auto &entity_components = this->m_entities_components[entity];

				return (entity_components.find(component_type_id) != entity_components.end());
			}


			template <typename T>
			T &get(const PULSAR::ecs::entity entity)
			{
				const PULSAR::ecs::component_type_id component_type_id = PULSAR::ecs::component_type::id<T>();
				assert(("Component type id overflow", component_type_id < MAX_COMPONENTS_TYPES));
				assert(("Entity id is invalid", this->m_entities_signatures.find(entity) != this->m_entities_signatures.end()));

				return (*((T *)this->m_entities_components[entity][component_type_id]));
			}

			template <typename T, typename... Ts>
			const PULSAR::ecs::group	group()
			{
				std::tuple<T, Ts...> tup;
				signature sig = this->read_type_bits(tup);

				return (this->m_entity_tree.group(sig));
			}


			void	register_system(PULSAR::ecs::system *system)
			{
				this->m_systems.push_back(system);
			}

			void	execute_systems()
			{
				for (auto *system : this->m_systems)
				{
					system->execute();
				}
			}
		};
	}
}
