
#include "ecs/types.h"


std::unordered_map<size_t, PULSAR::ecs::component_type_id>	PULSAR::ecs::component_type::s_hash_id;
PULSAR::ecs::component_type_id	PULSAR::ecs::component_type::s_count = 0ull;
