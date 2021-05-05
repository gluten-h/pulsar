
#include "grng_shader_manager.h"


GRNG_SHADER				*grng_sm::get_shader_secure(unsigned int id)
{
	GRNG_SHADER *shader_ptr = grng_sm::shader.get_secure(id);
	if (!shader_ptr)
		return (NULL);
	return (shader_ptr);
}

GRNG_SHADER				*grng_sm::get_shader(unsigned int id)
{
	GRNG_SHADER *shader_ptr = grng_sm::shader.get(id);
	return (shader_ptr);
}


ID3D11VertexShader		*grng_sm::get_vert_shader_secure(unsigned int id)
{
	GRNG_SHADER *shader_ptr = grng_sm::shader.get_secure(id);
	if (!shader_ptr || shader_ptr->type != GRNG_SHADER_TYPE::GRNG_VERT_SHADER)
		return (NULL);
	return ((ID3D11VertexShader*)shader_ptr->shader);
}

ID3D11VertexShader		*grng_sm::get_vert_shader(unsigned int id)
{
	GRNG_SHADER *shader_ptr = grng_sm::shader.get(id);
	return ((ID3D11VertexShader*)shader_ptr->shader);
}


ID3D11GeometryShader	*grng_sm::get_geom_shader_secure(unsigned int id)
{
	GRNG_SHADER *shader_ptr = grng_sm::shader.get_secure(id);
	if (!shader_ptr || shader_ptr->type != GRNG_SHADER_TYPE::GRNG_GEOM_SHADER)
		return (NULL);
	return ((ID3D11GeometryShader*)shader_ptr->shader);
}

ID3D11GeometryShader	*grng_sm::get_geom_shader(unsigned int id)
{
	GRNG_SHADER *shader_ptr = grng_sm::shader.get(id);
	return ((ID3D11GeometryShader*)shader_ptr->shader);
}


ID3D11PixelShader	*grng_sm::get_frag_shader_secure(unsigned int id)
{
	GRNG_SHADER *shader_ptr = grng_sm::shader.get_secure(id);
	if (!shader_ptr || shader_ptr->type != GRNG_SHADER_TYPE::GRNG_FRAG_SHADER)
		return (NULL);
	return ((ID3D11PixelShader*)shader_ptr->shader);
}
ID3D11PixelShader	*grng_sm::get_frag_shader(unsigned int id)
{
	GRNG_SHADER *shader_ptr = grng_sm::shader.get(id);
	return ((ID3D11PixelShader*)shader_ptr->shader);
}



const GRNG_IPISTON<GRNG_SHADER, GRNG_MAX_SHADER_COUNT>	*grng_sm::get_ishader()
{
	return (grng_sm::ishader);
}
