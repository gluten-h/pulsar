#pragma once

#include <stdint.h>


namespace pulsar
{
	const uint16_t MAX_JOBS_PER_RQ = 1024u;

	enum RENDERING_MODE
	{
		RQ_OPAQUE,
		RENDERING_MODES_COUNT
	};
}
