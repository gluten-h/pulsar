
#include <unordered_map>
#include <vector>


namespace PULSAR
{
	namespace rg
	{
		class input;
		class source;

		class pass
		{
		private:
			std::string m_name;

			std::unordered_map<std::string, PULSAR::rg::input*> m_inputs;
			std::unordered_map<std::string, PULSAR::rg::source*> m_sources;

		public:
			pass &operator=(const pass&) = delete;
			pass &operator=(pass&&) = delete;
			pass(const pass&) = delete;
			pass(pass&&) = delete;
			pass() = delete;
			pass(const std::string &name);
			~pass() = default;

			const std::string	&name() const;

			void	register_input(PULSAR::rg::input *input);
			void	register_source(PULSAR::rg::source *source);
			void	link_input(const std::string &input_name, const std::string &source_path);

			PULSAR::rg::input	*get_input(const std::string &input_name);
			PULSAR::rg::source	*get_source(const std::string &source_name);
			std::unordered_map<std::string, PULSAR::rg::input*>		&get_all_inputs();

			virtual void	validate() const;
			virtual void	execute() = 0;
		};
	}
}
