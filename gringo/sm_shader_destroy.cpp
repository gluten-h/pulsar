
#include "grng_shader_manager.h"


void	grng_sm::destroy_vert_shader(GRNG_SHADER *&shader_ptr)
{
	ID3D11VertexShader *vs = (ID3D11VertexShader*)shader_ptr->shader;
	vs->Release();
	if (shader_ptr->layout)
		shader_ptr->layout->Release();

	shader_ptr->shader = NULL;
	shader_ptr->layout = NULL;
	shader_ptr->shader_blob = NULL;
}

void	grng_sm::destroy_geom_shader(GRNG_SHADER *&shader_ptr)
{
	ID3D11GeometryShader *gs = (ID3D11GeometryShader*)shader_ptr->shader;
	gs->Release();
	shader_ptr->shader_blob->Release();

	shader_ptr->shader = NULL;
	shader_ptr->shader_blob = NULL;
}

void	grng_sm::destroy_frag_shader(GRNG_SHADER *&shader_ptr)
{
	ID3D11PixelShader *fs = (ID3D11PixelShader*)shader_ptr->shader;
	fs->Release();
	shader_ptr->shader_blob->Release();

	shader_ptr->shader = NULL;
	shader_ptr->shader_blob = NULL;
}


void	grng_sm::destroy_shader_memory(unsigned int id)
{
	GRNG_SHADER *shader_ptr = grng_sm::shader.get(id);
	switch (shader_ptr->type)
	{
		case GRNG_SHADER_TYPE::GRNG_VERT_SHADER:
		{
			grng_sm::destroy_vert_shader(shader_ptr);
			break;
		}
		case GRNG_SHADER_TYPE::GRNG_GEOM_SHADER:
		{
			grng_sm::destroy_geom_shader(shader_ptr);
			break;
		}
		case GRNG_SHADER_TYPE::GRNG_FRAG_SHADER:
		{
			grng_sm::destroy_frag_shader(shader_ptr);
			break;
		}
	}

	grng_sm::shader.remove(id);
}

void	grng_sm::destroy_shader_secure(unsigned int id)
{
	GRNG_SHADER *shader_ptr = grng_sm::shader.get_secure(id);
	if (id >= GRNG_MAX_SHADER_COUNT || !shader_ptr)
		return;

	grng_sm::destroy_shader_memory(id);
}

void	grng_sm::destroy_shader(unsigned int id)
{
	grng_sm::destroy_shader_memory(id);
}

