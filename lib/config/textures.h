#pragma once

#include "texture.h"


namespace PULSAR
{
	const LPCWSTR STD_QUAD_WHITE_PATH = L"resources/std/quad_white.png";
	const LPCWSTR STD_QUAD_BLACK_PATH = L"resources/std/quad_black.png";
	const LPCWSTR STD_QUAD_NORMAL_PATH = L"resources/std/quad_normal.png";


	const PULSAR::TEXTURE STD_QUAD_WHITE_TEX = PULSAR::TEXTURE(STD_QUAD_WHITE_PATH);
	const PULSAR::TEXTURE STD_QUAD_BLACK_TEX = PULSAR::TEXTURE(STD_QUAD_BLACK_PATH);
	const PULSAR::TEXTURE STD_QUAD_NORMAL_TEX = PULSAR::TEXTURE(STD_QUAD_NORMAL_PATH);
}
