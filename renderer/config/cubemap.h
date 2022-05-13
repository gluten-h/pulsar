#pragma once

#include "cubemap/cubemap.h"


#define CUBEMAP_BLACK_PATH L"resources/pulsar/cubemap_black.dds"
#define CUBEMAP_WHITE_PATH L"resources/pulsar/cubemap_white.dds"

namespace PULSAR
{
	const PULSAR::cubemap CUBEMAP_BLACK(CUBEMAP_BLACK_PATH);
	const PULSAR::cubemap CUBEMAP_WHITE(CUBEMAP_WHITE_PATH);
}
