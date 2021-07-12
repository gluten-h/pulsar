
#include "grng_skybox.h"


void		grng_skybox::update_transform()
{
	this->vert_transform.view = GRNG_GFX::get_curr_camera()->get_view_matrix();
	this->vert_transform.proj = GRNG_GFX::get_curr_camera()->get_proj_matrix();

	grng_skybox::transform_cbuffer.update(this->vert_transform);
	grng_skybox::transform_cbuffer.bind();
}

void		grng_skybox::set_env_map(const GRNG_CUBEMAP &env_map)
{
	this->env_map = (GRNG_CUBEMAP*)&env_map;
}

void		grng_skybox::set_mesh(GRNG_MESH &mesh)
{
	this->mesh = &mesh;
}
