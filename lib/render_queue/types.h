#pragma once

#include <stdint.h>


namespace pulsar
{
	const uint16_t MAX_JOBS_PER_RQ = 1024u;

	enum RQ_MODE
	{
		RQ_OPAQUE,
		RQ_MODES_COUNT
	};
}
