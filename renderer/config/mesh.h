#pragma once

#include "config.h"
#include "mesh/mesh.h"


namespace pulsar
{
	//	TODO: create primitive class inherited from mesh and write geometry data directly in constructor
	const pulsar::mesh CUBE = pulsar::mesh(pulsar::CUBE_OBJ_PATH, pulsar::MESH_FILE_FORMAT::OBJ);
	
	const pulsar::mesh SPHERE16;// = pulsar::mesh(pulsar::SPHERE16_OBJ_PATH, pulsar::MESH_FILE_FORMAT::OBJ);
	const pulsar::mesh SPHERE32;// = pulsar::mesh(pulsar::SPHERE32_OBJ_PATH, pulsar::MESH_FILE_FORMAT::OBJ);
	const pulsar::mesh SPHERE64 = pulsar::mesh(pulsar::SPHERE64_OBJ_PATH, pulsar::MESH_FILE_FORMAT::OBJ);
}
