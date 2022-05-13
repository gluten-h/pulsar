#pragma once

#include "shader_texture/shader_texture.h"


#define WHITE_QUAD_PATH L"resources/pulsar/quad_white.png"
#define BLACK_QUAD_PATH L"resources/pulsar/quad_black.png"
#define NORMAL_QUAD_PATH L"resources/pulsar/quad_normal.png"

namespace PULSAR
{
	const PULSAR::shader_texture WHITE_QUAD_TEXTURE(WHITE_QUAD_PATH);
	const PULSAR::shader_texture BLACK_QUAD_TEXTURE(BLACK_QUAD_PATH);
	const PULSAR::shader_texture NORMAL_QUAD_TEXTURE(NORMAL_QUAD_PATH);
}
