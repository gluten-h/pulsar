#pragma once

#include "mesh/mesh.h"


#define CUBE_OBJ_PATH L"resources/std/cube.obj"

#define SPHERE16_OBJ_PATH L"resources/std/sphere16.obj"
#define SPHERE32_OBJ_PATH L"resources/std/sphere32.obj"
#define SPHERE64_OBJ_PATH L"resources/std/sphere64.obj"

namespace PULSAR
{
	const PULSAR::mesh CUBE;// = PULSAR::mesh(STD_CUBE_OBJ_PATH, PULSAR::MESH_FILE_FORMAT::OBJ);
	
	const PULSAR::mesh SPHERE16;// = PULSAR::mesh(STD_SPHERE16_OBJ_PATH, PULSAR::MESH_FILE_FORMAT::OBJ);
	const PULSAR::mesh SPHERE32;// = PULSAR::mesh(STD_SPHERE32_OBJ_PATH, PULSAR::MESH_FILE_FORMAT::OBJ);
	const PULSAR::mesh SPHERE64;// = PULSAR::mesh(STD_SPHERE64_OBJ_PATH, PULSAR::MESH_FILE_FORMAT::OBJ);
}
