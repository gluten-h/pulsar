#pragma once

#include "render_graph/pass.h"
#include "render_queue/render_queue.h"


namespace PULSAR
{
	class render_queue_pass : public PULSAR::rg::pass
	{
	public:
		render_queue_pass &operator=(const render_queue_pass&) = delete;
		render_queue_pass &operator=(render_queue_pass&&) = delete;
		render_queue_pass(const render_queue_pass&) = delete;
		render_queue_pass(render_queue_pass&&) = delete;
		render_queue_pass() = delete;
		render_queue_pass(const std::string &name) : PULSAR::rg::pass(name){ }
		~render_queue_pass() = default;

		void	execute(float delta_time) override
		{
			//PULSAR::render_queue::get().execute();
		}
	};
}
