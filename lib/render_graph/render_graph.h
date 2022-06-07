#pragma once

#include <vector>
#include <unordered_map>
#include <map>
#include <string>

namespace pulsar
{
	namespace rg
	{
		class source;
		class pass;

		class render_graph
		{
		private:
			std::unordered_map<std::string, pulsar::rg::source*> m_global_sources;

			std::unordered_map<std::string, pulsar::rg::pass*> m_passes_reg;
			std::map<uint8_t, std::vector<pulsar::rg::pass*>> m_passes_levels;
			std::vector<std::vector<pulsar::rg::pass*>> m_passes;

			void	link_pass(pulsar::rg::pass *pass);

		protected:
			void	compile();
			void	validate() const;

		public:
			render_graph &operator=(const render_graph&) = delete;
			render_graph &operator=(render_graph&&) = delete;
			render_graph(const render_graph&) = delete;
			render_graph(render_graph&&) = delete;
			render_graph() = default;
			~render_graph() = default;

			void	register_global_source(pulsar::rg::source *source);
			void	add_pass(uint8_t level, pulsar::rg::pass *pass);

			void	execute();
		};
	}
}
