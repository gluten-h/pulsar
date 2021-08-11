
#include "grng_skybox.h"


void		grng_skybox::set_material(const GRNG_SKYBOX_MATERIAL &mat)
{
	this->material = (GRNG_SKYBOX_MATERIAL*)&mat;
}

void		grng_skybox::set_material(GRNG_SKYBOX_MATERIAL *mat)
{
	this->material = mat;
}

void		grng_skybox::set_mesh(const GRNG_MESH &mesh)
{
	this->mesh = (GRNG_MESH*)&mesh;
}

void		grng_skybox::set_mesh(GRNG_MESH *mesh)
{
	this->mesh = mesh;
}
