#pragma once

#include <vector>


namespace pulsar
{
	template <typename T, uint8_t RQ_MODES_COUNT>
	class render_queue
	{
	private:
		struct rq_stack
		{
			uint16_t m_curr_job_id = 0u;
			std::vector<T> m_jobs;
		};

	protected:
		rq_stack m_queues[RQ_MODES_COUNT];

		render_queue &operator=(const render_queue&) = delete;
		render_queue &operator=(render_queue&&) = delete;
		render_queue(const render_queue&) = delete;
		render_queue(render_queue&&) = delete;
		render_queue() = delete;
		render_queue(uint16_t max_jobs)
		{
			int i = -1;
			while (++i < RQ_MODES_COUNT)
				this->m_queues[i].m_jobs.resize(max_jobs);
		}
		virtual ~render_queue() = default;

	public:
		void	submit_job(uint8_t mode, T &&job)
		{
			auto &mode_queue = this->m_queues[mode];
			mode_queue.m_jobs[mode_queue.m_curr_job_id++] = std::move(job);
		}

		void	clear()
		{
			int i = -1;
			while (++i < RQ_MODES_COUNT)
				this->m_queues[i].m_curr_job_id = 0u;
		}

		void	execute()
		{
			int i = -1;
			while (++i < RQ_MODES_COUNT)
			{
				int j = -1;
				while (++j < this->m_queues[i].m_curr_job_id)
					this->m_queues[i].m_jobs[j].execute();
			}
		}
	};
}
