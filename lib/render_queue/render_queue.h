#pragma once

#include "types.h"
#include "utils/singleton.h"
#include "job.h"
#include <array>
#include <vector>


namespace pulsar
{
	class render_queue : public pulsar::singleton<render_queue>
	{
	private:
		struct rq_job
		{
			uint16_t m_curr_job_id = 0u;
			std::vector<pulsar::job> m_jobs;
		};

	private:
		std::array<rq_job, RENDERING_MODE::RENDERING_MODES_COUNT> m_queues;

	public:
		render_queue &operator=(const render_queue&) = delete;
		render_queue &operator=(render_queue&&) = delete;
		render_queue(const render_queue&) = delete;
		render_queue(render_queue&&) = delete;
		render_queue();
		render_queue(uint16_t max_jobs);
		~render_queue() = default;

		void	add_job(pulsar::RENDERING_MODE mode, pulsar::job &&job);
		void	clear();
		void	execute() const noexcept;
	};
}
