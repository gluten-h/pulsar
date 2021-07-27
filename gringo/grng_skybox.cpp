
#include "grng_skybox.h"


void		grng_skybox::copy_assign(const grng_skybox &s)
{
	this->env_map = s.env_map;
	this->mesh = s.mesh;
}


grng_skybox		&grng_skybox::operator=(const grng_skybox &s)
{
	this->copy_assign(s);

	return (*this);
}

grng_skybox::grng_skybox(const grng_skybox &s)
{
	this->copy_assign(s);
}

grng_skybox::grng_skybox()
{
	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	grng_skybox::input_layout.set(grng_skybox::vs.get_shader_blob(), ied, (UINT)std::size(ied));
}
