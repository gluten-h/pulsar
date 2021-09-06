#pragma once

#include "bindable.h"
#include "bindable_entity.h"
#include "filesystem.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


namespace PULSAR
{
	enum class MESH_FILE_FORMAT
	{
		OBJ
	};


	class MESH : public PULSAR::BINDABLE
	{
	private:
		struct MESH_DATA
		{
			struct VERT_DATA
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

			std::vector<VERT_DATA>		verts;
			std::vector<UINT32>			indices;
			t_mesh_specs				mesh_specs;


			void	clear()
			{
				this->verts.clear();
				this->indices.clear();

				this->mesh_specs.n = false;
				this->mesh_specs.uv = false;
			}
		};

		MESH_DATA	mesh;

		D3D_PRIMITIVE_TOPOLOGY		primitive_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		ID3D11Buffer *v_buffer = NULL;
		ID3D11Buffer *i_buffer = NULL;

	protected:
		void		remove_from_entities() override
		{
			for (auto &it : this->entities)
				it->_remove_bindable_ignore_entity(this);
			this->entities.clear();
		}

	private:
		void	remove_v_buffer_memory();
		void	remove_i_buffer_memory();
		void	remove_mesh_memory();
		void	load_mesh_obj(LPCWSTR file);
		void	create_buffer();

		void	copy_assign(const MESH &m);

	public:
		using PULSAR::BINDABLE::bind;

	public:
		MESH	&operator=(const MESH &m);
		MESH(const MESH &m);
		MESH();
		MESH(LPCWSTR file, MESH_FILE_FORMAT file_format);
		~MESH();

		void	set(LPCWSTR file, MESH_FILE_FORMAT file_format);
		void	set_primitive_topology(const D3D_PRIMITIVE_TOPOLOGY &primitive_topology);

		static MESH		*create();

		void	bind() const override;
		void	unbind() const override;

		void	draw();
	};
}
