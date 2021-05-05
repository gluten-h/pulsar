#pragma once

#include "grng_d3d.h"
#include "grng_piston.h"

#include <unordered_map>


#define GRNG_MAX_SHADER_COUNT 64


#define GRNG_VERT_ENTRY_POINT "vert"
#define GRNG_GEOM_ENTRY_POINT "geom"
#define GRNG_FRAG_ENTRY_POINT "frag"

#define GRNG_VERT_TARGET "vs_5_0"
#define GRNG_GEOM_TARGET "gs_5_0"
#define GRNG_FRAG_TARGET "ps_5_0"


enum class			GRNG_SHADER_TYPE : int
{
	GRNG_VERT_SHADER,
	GRNG_GEOM_SHADER,
	GRNG_FRAG_SHADER
};


typedef struct			grng_shader
{
	GRNG_SHADER_TYPE	type;

	ID3D11InputLayout	*layout = NULL;
	void				*shader = NULL;
	ID3DBlob			*shader_blob = NULL;

}						GRNG_SHADER;


class grng_sm
{
private:
	static ID3D11Device		*device;

	static const std::unordered_map<GRNG_SHADER_TYPE, const LPCSTR>		type_entry_point;
	static const std::unordered_map<GRNG_SHADER_TYPE, const LPCSTR>		type_target;

	static GRNG_PISTON<GRNG_SHADER, GRNG_MAX_SHADER_COUNT>			shader;
	static const GRNG_IPISTON<GRNG_SHADER, GRNG_MAX_SHADER_COUNT>	*ishader;

private:
	static void			destroy_shader_memory(unsigned int id);

	static void			init_d3d();
	static void			init_shader();

	static void			create_vert_shader(ID3DBlob *shader, GRNG_SHADER *&shader_ptr);
	static void			create_geom_shader(ID3DBlob *shader, GRNG_SHADER *&shader_ptr);
	static void			create_frag_shader(ID3DBlob *shader, GRNG_SHADER *&shader_ptr);

	static void			destroy_vert_shader(GRNG_SHADER *&shader_ptr);
	static void			destroy_geom_shader(GRNG_SHADER *&shader_ptr);
	static void			destroy_frag_shader(GRNG_SHADER *&shader_ptr);

public:
	static void			create()
	{
		grng_sm::init_d3d();
		grng_sm::init_shader();
	}

	static void			destroy()
	{
		int i = -1;
		while (++i < GRNG_MAX_SHADER_COUNT)
		{
			grng_sm::shader.remove_secure(i);
		}
	}

	
	static int			create_shader(LPCWSTR shader_file, GRNG_SHADER_TYPE shader_type)
	{
		if (grng_sm::ishader->size >= GRNG_MAX_SHADER_COUNT)
			return (-1);

		HRESULT hr;

		const LPCSTR &entry_point = grng_sm::type_entry_point.at(shader_type);
		const LPCSTR &target = grng_sm::type_target.at(shader_type);

		ID3DBlob *shader_blob;
		hr = D3DCompileFromFile(shader_file, NULL, NULL, entry_point, target, NULL, NULL, &shader_blob, NULL);

		GRNG_SHADER *shader_ptr = grng_sm::shader.get(grng_sm::shader.next_id());
		switch (shader_type)
		{
			case GRNG_SHADER_TYPE::GRNG_VERT_SHADER:
			{
				grng_sm::create_vert_shader(shader_blob, shader_ptr);
				break;
			}
			case GRNG_SHADER_TYPE::GRNG_GEOM_SHADER:
			{
				grng_sm::create_geom_shader(shader_blob, shader_ptr);
				break;
			}
			case GRNG_SHADER_TYPE::GRNG_FRAG_SHADER:
			{
				grng_sm::create_frag_shader(shader_blob, shader_ptr);
				break;
			}
		}
		int shader_id = grng_sm::shader.add(*shader_ptr);

		return (shader_id);
	}

	static HRESULT		create_vert_shader_layout_secure(unsigned int id, D3D11_INPUT_ELEMENT_DESC *ied, UINT ied_num_elements);
	static HRESULT		create_vert_shader_layout(unsigned int id, D3D11_INPUT_ELEMENT_DESC *ied, UINT ied_num_elements);


	static void			destroy_shader_secure(unsigned int id);
	static void			destroy_shader(unsigned int id);

	static GRNG_SHADER			*get_shader_secure(unsigned int id);
	static GRNG_SHADER			*get_shader(unsigned int id);
	static ID3D11VertexShader	*get_vert_shader_secure(unsigned int id);
	static ID3D11VertexShader	*get_vert_shader(unsigned int id);
	static ID3D11GeometryShader	*get_geom_shader_secure(unsigned int id);
	static ID3D11GeometryShader	*get_geom_shader(unsigned int id);
	static ID3D11PixelShader	*get_frag_shader_secure(unsigned int id);
	static ID3D11PixelShader	*get_frag_shader(unsigned int id);

	static const GRNG_IPISTON<GRNG_SHADER, GRNG_MAX_SHADER_COUNT>		*get_ishader();
};


using GRNG_SM = grng_sm;

