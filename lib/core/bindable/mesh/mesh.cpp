
#include "mesh.h"


void	PULSAR::MESH::copy_assign(const MESH &m)
{
	this->mesh.clear();
	this->mesh.verts = m.mesh.verts;
	this->mesh.indices = m.mesh.indices;
	this->mesh.mesh_specs = m.mesh.mesh_specs;

	this->primitive_topology = m.primitive_topology;
	this->v_buffer = m.v_buffer;
	this->i_buffer = m.i_buffer;
	if (this->v_buffer)
		this->v_buffer->AddRef();
	if (this->i_buffer)
		this->i_buffer->AddRef();
}


PULSAR::MESH	&PULSAR::MESH::operator=(const MESH &m)
{
	if (this->v_buffer != m.v_buffer)
		this->remove_v_buffer_memory();
	if (this->i_buffer != m.i_buffer)
		this->remove_i_buffer_memory();
	this->copy_assign(m);

	return (*this);
}

PULSAR::MESH::MESH(const MESH &m) : PULSAR::BINDABLE()
{
	this->type = PULSAR::BINDABLE_TYPE::MESH;
	this->copy_assign(m);
}

PULSAR::MESH::MESH() : PULSAR::BINDABLE()
{
	this->type = PULSAR::BINDABLE_TYPE::MESH;
}

PULSAR::MESH::MESH(LPCWSTR file, PULSAR::MESH_FILE_FORMAT file_format) : PULSAR::BINDABLE()
{
	this->type = PULSAR::BINDABLE_TYPE::MESH;
	this->set(file, file_format);
}

PULSAR::MESH::~MESH()
{
	this->remove_mesh_memory();
}
