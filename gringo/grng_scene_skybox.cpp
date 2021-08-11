
#include "grng_scene.h"


void				grng_scene::set_skybox_material(const GRNG_SKYBOX_MATERIAL &mat)
{
	this->skybox.set_material(mat);
}

void				grng_scene::set_skybox_material(GRNG_SKYBOX_MATERIAL *mat)
{
	this->skybox.set_material(mat);
}

void				grng_scene::set_skybox_mesh(const GRNG_MESH &mesh)
{
	this->skybox.set_mesh(mesh);
}

void				grng_scene::set_skybox_mesh(GRNG_MESH *mesh)
{
	this->skybox.set_mesh(mesh);
}
