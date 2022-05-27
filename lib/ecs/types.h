#pragma once

#include <stdint.h>
#include <limits>
#include <typeinfo>
#include <unordered_map>
#include <span>


namespace pulsar
{
	namespace ecs
	{
		const size_t MAX_COMPONENTS_TYPES = 32ull;
		const size_t null = (std::numeric_limits<size_t>::max)();

		using entity = uint32_t;
		using component_type_id = uint32_t;

		using group = std::span<entity>;

		class component_type
		{
		private:
			static std::unordered_map<size_t, component_type_id> s_hash_id;
			static component_type_id s_count;

		public:
			template <typename T>
			static const component_type_id	id()
			{
				if (component_type::s_hash_id.find(typeid(T).hash_code()) == component_type::s_hash_id.end())
					component_type::s_hash_id[typeid(T).hash_code()] = component_type::s_count++;

				return (component_type::s_hash_id[typeid(T).hash_code()]);
			}
		};
	}
}
