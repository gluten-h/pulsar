
#include "grng_mesh.h"


void		grng_mesh::remove_v_buffer_memory()
{
	if (this->v_buffer)
	{
		ULONG ref_count = this->v_buffer->Release();
		if (ref_count == 0)
			this->v_buffer = NULL;
	}
}

void		grng_mesh::remove_i_buffer_memory()
{
	if (this->i_buffer)
	{
		ULONG ref_count = this->i_buffer->Release();
		if (ref_count == 0)
			this->i_buffer = NULL;
	}
}

void		grng_mesh::remove_mesh_memory()
{
	this->mesh.clear();

	this->remove_v_buffer_memory();
	this->remove_i_buffer_memory();
}

void		grng_mesh::set(LPCWSTR file, GRNG_MESH_FILE_FORMAT file_format)
{
	this->remove_mesh_memory();

	switch (file_format)
	{
		case GRNG_MESH_FILE_FORMAT::OBJ:
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


grng_mesh	*grng_mesh::create()
{
	grng_mesh *mesh = new grng_mesh;
	mesh->id = GRNG_BM.add(mesh);
	if (mesh->id == -1)
	{
		delete mesh;
		return (NULL);
	}
	mesh->is_alloc = true;

	return (mesh);
}
