#pragma once

#include <stddef.h>


namespace pulsar
{
	class transform;
	class mesh;

	class shadows_job
	{
	private:
		pulsar::transform *mp_transform = NULL;
		pulsar::mesh *mp_mesh = NULL;

	public:
		shadows_job &operator=(const shadows_job&) = delete;
		shadows_job &operator=(shadows_job&&) = default;
		shadows_job(const shadows_job&) = delete;
		shadows_job(shadows_job&&) = default;
		shadows_job() = default;
		shadows_job(pulsar::transform *transform, pulsar::mesh *mesh);
		~shadows_job() = default;

		void	execute() const;
	};
}
