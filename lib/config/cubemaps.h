#pragma once

#include "cubemap.h"


namespace PULSAR
{
	const LPCWSTR STD_CUBEMAP_BLACK_PATH = L"resources/std/cubemap_black.dds";
	const LPCWSTR STD_CUBEMAP_WHITE_PATH = L"resources/std/cubemap_white.dds";

	const PULSAR::CUBEMAP STD_CUBEMAP_BLACK = PULSAR::CUBEMAP(STD_CUBEMAP_BLACK_PATH);
	const PULSAR::CUBEMAP STD_CUBEMAP_WHITE = PULSAR::CUBEMAP(STD_CUBEMAP_WHITE_PATH);
}
