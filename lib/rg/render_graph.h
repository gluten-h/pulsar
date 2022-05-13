#pragma once

#include <vector>
#include <unordered_map>
#include <string>

namespace PULSAR
{
	namespace rg
	{
		class source;
		class pass;

		class render_graph
		{
		private:
			static render_graph *mp_active_rg;

		private:
			std::unordered_map<std::string, PULSAR::rg::source*> m_global_sources;

			std::unordered_map<std::string, PULSAR::rg::pass*> m_passes_reg;
			std::vector<std::vector<PULSAR::rg::pass*>> m_passes;

		private:
			void	link_pass(PULSAR::rg::pass *pass);

		public:
			static void	set_active(render_graph *rg);
			static render_graph	*get_active();

		protected:
			void	compile();
			void	validate() const;

		public:
			render_graph &operator=(const render_graph&) = delete;
			render_graph &operator=(render_graph&&) = delete;
			render_graph(const render_graph&) = delete;
			render_graph(render_graph&&) = delete;
			render_graph();
			~render_graph() = default;

			void	register_global_source(PULSAR::rg::source *source);
			void	add_pass(uint32_t level, PULSAR::rg::pass *pass);

			void	execute();
		};
	}
}
