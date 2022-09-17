#pragma once

#include <stddef.h>


namespace pulsar
{
	class transform;
	class mesh;
	class material;

	class viewport_job
	{
	private:
		pulsar::transform *mp_transform = NULL;
		pulsar::mesh *mp_mesh = NULL;
		pulsar::material *mp_material = NULL;

	public:
		viewport_job &operator=(const viewport_job&) = delete;
		viewport_job &operator=(viewport_job&&) = default;
		viewport_job(const viewport_job&) = delete;
		viewport_job(viewport_job&&) = default;
		viewport_job() = default;
		viewport_job(pulsar::transform *transform, pulsar::mesh *mesh, pulsar::material *material);
		~viewport_job() = default;

		void	execute() const;
	};
}
