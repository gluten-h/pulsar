
#include "grng_mesh.h"


void			grng_mesh::copy_assign(const grng_mesh &m)
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


grng_mesh		&grng_mesh::operator=(const grng_mesh &m)
{
	if (this->v_buffer != m.v_buffer)
		this->remove_v_buffer_memory();
	if (this->i_buffer != m.i_buffer)
		this->remove_i_buffer_memory();
	this->copy_assign(m);

	return (*this);
}

grng_mesh::grng_mesh(const grng_mesh &m) : GRNG_COMPONENT()
{
	this->type = GRNG_COMPONENT_TYPE::MESH;
	this->copy_assign(m);
}

grng_mesh::grng_mesh() : GRNG_COMPONENT()
{
	this->type = GRNG_COMPONENT_TYPE::MESH;
}

grng_mesh::grng_mesh(LPCWSTR file, GRNG_MESH_FILE_FORMAT file_format) : GRNG_COMPONENT()
{
	this->type = GRNG_COMPONENT_TYPE::MESH;
	this->set(file, file_format);
}

grng_mesh::~grng_mesh()
{
	this->remove_mesh_memory();
}
