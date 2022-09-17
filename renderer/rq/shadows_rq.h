#pragma once

#include "render_queue/render_queue.h"
#include "shadows_job.h"
#include "config/config.h"


namespace pulsar
{
	class shadows_rq : public pulsar::render_queue<pulsar::shadows_job, pulsar::SHADOWS_RQ_MODES_COUNT>
	{
	public:
		shadows_rq &operator=(const shadows_rq&) = delete;
		shadows_rq &operator=(shadows_rq&&) = delete;
		shadows_rq(const shadows_rq&) = delete;
		shadows_rq(shadows_rq&&) = delete;
		shadows_rq() : pulsar::render_queue<pulsar::shadows_job, pulsar::SHADOWS_RQ_MODES_COUNT>(pulsar::MAX_VIEWPORT_RQ_JOBS){ }
		~shadows_rq() = default;
	};
}
