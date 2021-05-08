
#include "grng_mesh.h"


void		grng_mesh::remove_mesh_memory()
{
	this->mesh.clear();

	if (this->v_buffer)
		this->v_buffer->Release();
	if (this->i_buffer)
		this->i_buffer->Release();
}

void		grng_mesh::set_mesh(const char *file, GRNG_MESH_FILE_FORMAT file_format)
{
	this->remove_mesh_memory();

	switch (file_format)
	{
		case GRNG_MESH_FILE_FORMAT::GRNG_MESH_FILE_OBJ:
		{
			this->load_mesh_obj(file);
			this->create_buffer();

			break;
		}
	}
}

void		grng_mesh::set_primitive_topology(const D3D_PRIMITIVE_TOPOLOGY &primitive_topology)
{
	this->primitive_topology = primitive_topology;
}
