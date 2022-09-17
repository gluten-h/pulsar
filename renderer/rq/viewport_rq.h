#pragma once

#include "render_queue/render_queue.h"
#include "viewport_job.h"
#include "config/config.h"


namespace pulsar
{
	class viewport_rq : public pulsar::render_queue<pulsar::viewport_job, pulsar::VIEWPORT_RQ_MODES_COUNT>
	{
	public:
		viewport_rq &operator=(const viewport_rq&) = delete;
		viewport_rq &operator=(viewport_rq&&) = delete;
		viewport_rq(const viewport_rq&) = delete;
		viewport_rq(viewport_rq&&) = delete;
		viewport_rq() : pulsar::render_queue<pulsar::viewport_job, pulsar::VIEWPORT_RQ_MODES_COUNT>(pulsar::MAX_VIEWPORT_RQ_JOBS){ }
		~viewport_rq() = default;
	};
}
