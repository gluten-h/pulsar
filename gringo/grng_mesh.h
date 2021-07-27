#pragma once

#include "grng_component.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


enum class GRNG_MESH_FILE_FORMAT
{
	OBJ
};


class grng_mesh : public GRNG_COMPONENT
{
private:
	friend class grng_manager_ptr;

private:
	struct GRNG_MESH_DATA
	{
		struct GRNG_VERT_DATA
		{
			float x = 0.0f, y = 0.0f, z = 0.0f;
			float nx = 0.0f, ny = 0.0f, nz = 0.0f;
			float uv_x = 0.0f, uv_y = 0.0f;
		};
		struct t_mesh_specs
		{
			bool n = false;
			bool uv = false;
		};

		std::vector<GRNG_VERT_DATA>		verts;
		std::vector<UINT32>				indices;
		t_mesh_specs					mesh_specs;


		void	clear()
		{
			this->verts.clear();
			this->indices.clear();

			this->mesh_specs.n = false;
			this->mesh_specs.uv = false;
		}
	};

	GRNG_MESH_DATA	mesh;

	D3D_PRIMITIVE_TOPOLOGY		primitive_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	ID3D11Buffer				*v_buffer = NULL;
	ID3D11Buffer				*i_buffer = NULL;

private:
	void		remove_v_buffer_memory();
	void		remove_i_buffer_memory();
	void		remove_mesh_memory();
	void		load_mesh_obj(LPCWSTR file);
	void		create_buffer();

	void		copy_assign(const grng_mesh &m);

	static GRNG_COMPONENT		*create_manager_ptr();

public:
	grng_mesh	&operator=(const grng_mesh &m);
	grng_mesh(const grng_mesh &m);
	grng_mesh();
	grng_mesh(LPCWSTR file, GRNG_MESH_FILE_FORMAT file_format);
	~grng_mesh();

	void		set(LPCWSTR file, GRNG_MESH_FILE_FORMAT file_format);
	void		set_primitive_topology(const D3D_PRIMITIVE_TOPOLOGY &primitive_topology);

	void		bind();
	void		draw();
};


using GRNG_MESH = grng_mesh;
