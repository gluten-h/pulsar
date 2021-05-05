
#include "grng_mesh.h"


void		grng_mesh::load_mesh_obj(const char *file)
{
	std::vector<float> verts;
	std::vector<float> normals;
	std::vector<float> uvs;

	std::ifstream is(file);
	if (!is)
		return;
	this->remove_mesh_memory();

	std::string line;
	while (std::getline(is, line, '\n'))
	{
		std::vector<std::string> split = GRNG_UTILS::str_split(line.c_str(), ' ');
		if (!split.size())
			continue;

		if (split[0] == "v")
		{
			float vx = std::stof(split[1]);
			float vy = std::stof(split[2]);
			float vz = std::stof(split[3]);

			verts.push_back(vx);
			verts.push_back(vy);
			verts.push_back(vz);

			continue;
		}
		if (split[0] == "vt")
		{
			float uv_x = std::stof(split[1]);
			float uv_y = std::stof(split[2]);

			uvs.push_back(uv_x);
			uvs.push_back(uv_y);

			continue;
		}
		if (split[0] == "vn")
		{
			float nx = std::stof(split[1]);
			float ny = std::stof(split[2]);
			float nz = std::stof(split[3]);

			normals.push_back(nx);
			normals.push_back(ny);
			normals.push_back(nz);

			continue;
		}
		if (split[0] == "f")
		{
			int i = -1;
			while (++i < 3)
			{
				std::vector<std::string> vert_info = GRNG_UTILS::str_split(split[(UINT64)i + 1].c_str(), '/');

				int vert_id = std::stoi(vert_info[0]) - 1;
				grng_mesh::GRNG_MESH_DATA::GRNG_VERT_DATA vert;
				vert.x = verts[(UINT64)vert_id * 3 + 0];
				vert.y = verts[(UINT64)vert_id * 3 + 1];
				vert.z = verts[(UINT64)vert_id * 3 + 2];

				if (vert_info.size() >= 2 && !vert_info[1].empty())
				{
					this->mesh.mesh_specs.uv = true;
					int uv_id = std::stoi(vert_info[1]) - 1;

					vert.uv_x = uvs[(UINT64)uv_id * 2 + 0];
					vert.uv_y = uvs[(UINT64)uv_id * 2 + 1];
				}
				if (vert_info.size() > 2)
				{
					this->mesh.mesh_specs.n = true;
					int normal_id = std::stoi(vert_info[2]) - 1;

					vert.nx = normals[(UINT64)normal_id * 3 + 0];
					vert.ny = normals[(UINT64)normal_id * 3 + 1];
					vert.nz = normals[(UINT64)normal_id * 3 + 2];
				}

				this->mesh.verts.push_back(vert);
				this->mesh.indices.push_back(this->mesh.indices.size());
			}
		}
	}

	verts.clear();
	normals.clear();
	uvs.clear();
}
