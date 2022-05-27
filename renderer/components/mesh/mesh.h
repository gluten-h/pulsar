#pragma once

#include "gfx/gfx.h"
#include <vector>


namespace pulsar
{
	enum class MESH_FILE_FORMAT
	{
		OBJ
	};

	class mesh
	{
	private:
		struct mesh_data
		{
			struct vert_data
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

			std::vector<vert_data> m_verts;
			std::vector<UINT32> m_indices;
			t_mesh_specs m_mesh_specs;

			void	clear()
			{
				this->m_verts.clear();
				this->m_indices.clear();

				this->m_mesh_specs.n = false;
				this->m_mesh_specs.uv = false;
			}
		};

		mesh_data m_mesh_data;
		D3D_PRIMITIVE_TOPOLOGY m_primitive_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		ID3D11Buffer *mp_vertex_buffer = NULL;
		ID3D11Buffer *mp_index_buffer = NULL;

	private:
		bool	load_mesh_obj(LPCWSTR file);
		void	create_mesh();
		void	free();

	public:
		mesh &operator=(const mesh&) = delete;
		mesh &operator=(mesh&&) = delete;
		mesh(const mesh&) = delete;
		mesh(mesh&&) = delete;
		mesh() = default;
		mesh(LPCWSTR file, MESH_FILE_FORMAT file_format);
		~mesh();

		void	set(LPCWSTR file, MESH_FILE_FORMAT file_format);
		void	set_primitive_topology(D3D_PRIMITIVE_TOPOLOGY primitive_topology);

		UINT	get_index_count() const noexcept;

		void	bind() const;
		void	unbind() const;
	};
}
