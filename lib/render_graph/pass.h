#pragma once

#include <unordered_map>
#include <vector>
#include <string>


namespace pulsar
{
	namespace rg
	{
		class input;
		class source;

		class pass
		{
		private:
			std::string m_name;

			std::unordered_map<std::string, pulsar::rg::input*> m_inputs;
			std::unordered_map<std::string, pulsar::rg::source*> m_sources;

		public:
			pass &operator=(const pass&) = delete;
			pass &operator=(pass&&) = delete;
			pass(const pass&) = delete;
			pass(pass&&) = delete;
			pass() = delete;
			pass(const std::string &name);
			~pass() = default;

			const std::string	&name() const;

			void	register_input(pulsar::rg::input *input);
			void	register_source(pulsar::rg::source *source);
			void	link_input(const std::string &input_name, const std::string &source_path);

			pulsar::rg::input	*get_input(const std::string &input_name);
			pulsar::rg::source	*get_source(const std::string &source_name);
			std::unordered_map<std::string, pulsar::rg::input*>		&get_all_inputs();

			virtual void	validate() const;
			virtual void	execute() = 0;
		};
	}
}
