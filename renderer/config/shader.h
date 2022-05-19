#pragma once

#include "shaders/vert_shader.h"
#include "shaders/frag_shader.h"


#define FULLSCREEN_VS_PATH L"shaders/utils/fullscreen_vs.hlsl"
#define OPAQUE_GEOMETRY_G_BUFFER_FS_PATH L"shaders/g_buffer/g_buffer_pass_fs.hlsl"

namespace PULSAR
{
	const PULSAR::vert_shader FULLSCREEN_VS(FULLSCREEN_VS_PATH);
	const PULSAR::frag_shader OPAQUE_GEOMETRY_G_BUFFER_FS(OPAQUE_GEOMETRY_G_BUFFER_FS_PATH);
}