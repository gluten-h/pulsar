
#include "scene.h"


void		PULSAR::SCENE::set_skybox_material(const PULSAR::SKYBOX_MATERIAL &mat)
{
	this->skybox.set_material(mat);
}

void		PULSAR::SCENE::set_skybox_material(PULSAR::SKYBOX_MATERIAL *mat)
{
	this->skybox.set_material(mat);
}

void		PULSAR::SCENE::set_skybox_mesh(const PULSAR::MESH &mesh)
{
	this->skybox.set_mesh(mesh);
}

void		PULSAR::SCENE::set_skybox_mesh(PULSAR::MESH *mesh)
{
	this->skybox.set_mesh(mesh);
}
