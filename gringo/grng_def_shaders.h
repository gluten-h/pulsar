#pragma once

#include "grng_shaders.h"


#define GRNG_FULLSCREEN_HLSL L"fullscreen_vs.hlsl"


const GRNG_VERT_SHADER GRNG_FULLSCREEN_VS = GRNG_VERT_SHADER(GRNG_FULLSCREEN_HLSL, GRNG_VERT_ENTRY, NULL);
