#pragma once

#include "entt/entt.h"


namespace pulsar
{
	namespace ecs
	{
		using entity = entt::entity;
		inline constexpr auto null = entt::null;

		using registry = entt::registry;
	}
}
