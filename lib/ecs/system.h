#pragma once


namespace PULSAR
{
	namespace ecs
	{
		class registry;

		class system
		{
		private:
			const PULSAR::ecs::registry *mp_registry = NULL;

			system(const PULSAR::ecs::registry *p_registry) : mp_registry(p_registry){ }

		public:
			virtual void	execute(float delta_time) = 0;
		};
	}
}
