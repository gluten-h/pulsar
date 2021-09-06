#pragma once

#include "shaders.h"


namespace PULSAR
{
	const LPCWSTR FULLSCREEN_VS_HLSL = L"shaders/utils/fullscreen_vs.hlsl";			//	TODO: PATH

	const PULSAR::VERT_SHADER FULLSCREEN_VS = PULSAR::VERT_SHADER(FULLSCREEN_VS_HLSL, PULSAR::VERT_SHADER_ENTRY, NULL);

}