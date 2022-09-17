
#include "viewport_job.h"
#include "gfx/gfx.h"
#include "transform/transform.h"
#include "mesh/mesh.h"
#include "material/material.h"


pulsar::viewport_job::viewport_job(pulsar::transform *transform, pulsar::mesh *mesh, pulsar::material *material)
{
	this->mp_transform = transform;
	this->mp_mesh = mesh;
	this->mp_material = material;
}

void	pulsar::viewport_job::execute() const
{
	this->mp_transform->bind();
	this->mp_mesh->bind();
	this->mp_material->bind();
	pulsar::gfx::instance().draw_indexed(this->mp_mesh->get_index_count());

	this->mp_material->unbind();
	this->mp_mesh->unbind();
	this->mp_transform->unbind();
}
