
#include "ecs/types.h"


std::unordered_map<size_t, pulsar::ecs::component_type_id>	pulsar::ecs::component_type::s_hash_id;
pulsar::ecs::component_type_id	pulsar::ecs::component_type::s_count = 0ull;
