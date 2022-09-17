
#include "shadows_rq.h"
#include "gfx/gfx.h"
#include "transform/transform.h"
#include "mesh/mesh.h"


pulsar::shadows_job::shadows_job(pulsar::transform *transform, pulsar::mesh *mesh)
{
	this->mp_transform = transform;
	this->mp_mesh = mesh;
}

void	pulsar::shadows_job::execute() const
{
	this->mp_transform->bind();
	this->mp_mesh->bind();
	pulsar::gfx::instance().draw_indexed(this->mp_mesh->get_index_count());

	this->mp_mesh->unbind();
	this->mp_mesh->unbind();
}
