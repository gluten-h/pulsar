
#include <string>


namespace PULSAR
{
	namespace rg
	{
		class source;

		class input
		{
		private:
			std::string m_name;
			std::string m_source_name;
			std::string m_source_pass_name;

		protected:
			input(const std::string &name);

		public:
			input &operator=(const input&) = delete;
			input &operator=(input&&) = delete;
			input(const input&) = delete;
			input(input&&) = delete;
			input() = delete;
			virtual ~input() = default;

			const std::string	&name() const;
			const std::string	&source_name() const;
			const std::string	&source_pass_name() const;

			void	set_source(const std::string &source_pass_name, const std::string &source_name);

			virtual void	validate() const;
			virtual void	bind(PULSAR::rg::source *source) = 0;
		};
	}
}
