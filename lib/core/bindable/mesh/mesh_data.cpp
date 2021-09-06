
#include "mesh.h"


void		PULSAR::MESH::remove_v_buffer_memory()
{
	if (this->v_buffer)
	{
		ULONG ref_count = this->v_buffer->Release();
		if (ref_count == 0)
			this->v_buffer = NULL;
	}
}

void		PULSAR::MESH::remove_i_buffer_memory()
{
	if (this->i_buffer)
	{
		ULONG ref_count = this->i_buffer->Release();
		if (ref_count == 0)
			this->i_buffer = NULL;
	}
}

void		PULSAR::MESH::remove_mesh_memory()
{
	this->mesh.clear();

	this->remove_v_buffer_memory();
	this->remove_i_buffer_memory();
}

void		PULSAR::MESH::set(LPCWSTR file, PULSAR::MESH_FILE_FORMAT file_format)
{
	this->remove_mesh_memory();

	switch (file_format)
	{
		case PULSAR::MESH_FILE_FORMAT::OBJ:
		{
			this->load_mesh_obj(PULSAR::FILESYSTEM::file_path(file).c_str());
			this->create_buffer();

			break;
		}
	}
}

void		PULSAR::MESH::set_primitive_topology(const D3D_PRIMITIVE_TOPOLOGY &primitive_topology)
{
	this->primitive_topology = primitive_topology;
}


PULSAR::MESH	*PULSAR::MESH::create()
{
	return ((PULSAR::MESH*)PULSAR::BINDABLE::add_to_manager(new PULSAR::MESH));
}
