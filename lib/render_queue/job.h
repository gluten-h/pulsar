#pragma once

#include <stddef.h>


namespace pulsar
{
	class transform;
	class mesh;
	class material;

	class job
	{
	private:
		pulsar::transform *mp_transform = NULL;
		pulsar::mesh *mp_mesh = NULL;
		pulsar::material *mp_material = NULL;

	public:
		job &operator=(const job&) = delete;
		job &operator=(job&&) = default;
		job(const job&) = delete;
		job(job&&) = default;
		job() = default;
		job(pulsar::transform *transform, pulsar::mesh *mesh, pulsar::material *material);
		~job() = default;

		void	execute() const noexcept;
	};
}
