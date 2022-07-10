
#include "render_queue.h"


pulsar::render_queue::render_queue()
{
	int i = -1;
	while (++i < pulsar::RQ_MODE::RQ_MODES_COUNT)
		this->m_queues[i].m_jobs.resize(pulsar::MAX_JOBS_PER_RQ);
}

pulsar::render_queue::render_queue(uint16_t max_jobs)
{
	int i = -1;
	while (++i < pulsar::RQ_MODE::RQ_MODES_COUNT)
		this->m_queues[i].m_jobs.resize(max_jobs);
}

void	pulsar::render_queue::add_job(pulsar::RQ_MODE mode, pulsar::job &&job)
{
	auto &mode_queue = this->m_queues[mode];
	mode_queue.m_jobs[mode_queue.m_curr_job_id++] = std::move(job);
}

void	pulsar::render_queue::clear()
{
	int i = -1;
	while (++i < pulsar::RQ_MODE::RQ_MODES_COUNT)
		this->m_queues[i].m_curr_job_id = 0u;
}

void	pulsar::render_queue::execute() const noexcept
{
	int i = -1;
	while (++i < pulsar::RQ_MODE::RQ_MODES_COUNT)
	{
		int j = -1;
		while (++j < this->m_queues[i].m_curr_job_id)
			this->m_queues[i].m_jobs[j].execute();
	}
}
