
#include "skybox.h"


void	PULSAR::SKYBOX::set_material(const PULSAR::SKYBOX_MATERIAL &mat)
{
	this->material = (PULSAR::SKYBOX_MATERIAL*)&mat;
}

void	PULSAR::SKYBOX::set_material(PULSAR::SKYBOX_MATERIAL *mat)
{
	this->material = mat;
}

void	PULSAR::SKYBOX::set_mesh(const PULSAR::MESH &mesh)
{
	this->mesh = (PULSAR::MESH*)&mesh;
}

void	PULSAR::SKYBOX::set_mesh(PULSAR::MESH *mesh)
{
	this->mesh = mesh;
}
