#pragma once

#include "grng_scene_def.h"
#include "grng_texture.h"


#define GRNG_STD_QUAD_WHITE L"resources/std/grng_quad_white.png"
#define GRNG_STD_QUAD_BLACK L"resources/std/grng_quad_black.png"
#define GRNG_STD_QUAD_NORMAL L"resources/std/grng_quad_normal.png"

#define GRNG_STD_CUBE "resources/std/cube.obj"


const GRNG_TEXTURE GRNG_STD_QUAD_WHITE_TEX = GRNG_TEXTURE(GRNG_STD_QUAD_WHITE);
const GRNG_TEXTURE GRNG_STD_QUAD_BLACK_TEX = GRNG_TEXTURE(GRNG_STD_QUAD_BLACK);
const GRNG_TEXTURE GRNG_STD_QUAD_NORMAL_TEX = GRNG_TEXTURE(GRNG_STD_QUAD_NORMAL);


#define GRNG_MAX_SCENE_COUNT 64
#define GRNG_MAX_BINDABLE_COUNT 256

#define GRNG_MAX_CAMERA_COUNT 8
