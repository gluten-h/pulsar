//#pragma once
//
//#include "rg_inputs.h"
//#include "rg_sources.h"
//
//#include "utils.h"
//
//#include <string>
//#include <unordered_map>
//#include <stdexcept>
//
//
//namespace PULSAR
//{
//	class RG_PASS : public PULSAR::RG_COMPONENT
//	{
//	private:
//		std::string		name;
//
//		int		dependency_level = -1;
//
//		std::unordered_map<std::string, PULSAR::RG_INPUT*>		inputs;
//		std::unordered_map<std::string, PULSAR::RG_SOURCE*>		sources;
//
//
//		void		copy_assign(const rg_pass &p)
//		{
//			this->name = p.name;
//			this->inputs = p.inputs;
//			this->sources = p.sources;
//		}
//
//	public:
//		RG_PASS		&operator=(const RG_PASS &p)
//		{
//			this->copy_assign(p);
//
//			return (*this);
//		}
//		RG_PASS(const RG_PASS &p)
//		{
//			this->type = PULSAR::RG_COMPONENT_TYPE::PASS;
//			this->copy_assign(p);
//		}
//		RG_PASS(const std::string &name)
//		{
//			this->type = PULSAR::RG_COMPONENT_TYPE::PASS;
//			this->name = name;
//		}
//
//		void	register_input(RG_INPUT *input)
//		{
//			const std::string input_name = input->get_name();
//			try
//			{
//				this->inputs.at(input_name);
//				THROW_RG_EXC("RG_PASS " + this->name + ": Input " + input_name + " already exists");
//
//				return;
//			}
//			catch (const std::out_of_range ex){ }
//
//			this->inputs[input_name] = input;
//		}
//		void	register_source(PULSAR::RG_SOURCE *source)
//		{
//			const std::string source_name = source->get_name();
//			try
//			{
//				this->sources.at(source_name);
//				THROW_RG_EXC("RG_PASS " + this->name + ": Source " + source_name + " already exists");
//
//				return;
//			}
//			catch (const std::out_of_range &ex){ }
//
//			this->sources[source_name] = source;
//		}
//
//		void	set_dependency_level(unsigned int dependency_level)
//		{
//			this->dependency_level = dependency_level;
//		}
//		int		get_dependency_level() const
//		{
//			return (this->dependency_level);
//		}
//
//		PULSAR::RG_INPUT	*get_input(const std::string &name)
//		{
//			try
//			{
//				return (this->inputs.at(name));
//			}
//			catch (const std::out_of_range &ex)
//			{
//				THROW_RG_EXC("RG_PASS " + this->name + ": Input " + name + " not found");
//			}
//		}
//		PULSAR::RG_SOURCE	*get_source(const std::string &name)
//		{
//			try
//			{
//				return (this->sources.at(name));
//			}
//			catch (const std::out_of_range &ex)
//			{
//				THROW_RG_EXC("RG_PASS " + this->name + ": Source " + name + " not found");
//			}
//		}
//
//		std::string		get_name() const
//		{
//			return (this->name);
//		}
//		const std::unordered_map<std::string, RG_INPUT *>	get_inputs() const
//		{
//			return (this->inputs);
//		}
//
//
//		void	set_input_linkage(const std::string &input_name, const std::string &source)
//		{
//			RG_INPUT *input = this->get_input(input_name);
//			std::vector<std::string> source_split = UTILS::str_split(source, '.');
//			if (source_split.size() != 2u)
//				THROW_RG_EXC("RG_PASS " + this->name + ": Input source has invalid format");
//
//			input->set_source(source_split[0], source_split[1]);
//		}
//
//
//		virtual void	validate() const
//		{
//			for (auto &i : this->inputs)
//				i.second->validate();
//			for (auto &s : this->sources)
//				s.second->validate();
//		}
//
//		virtual void	execute() = 0;
//	};
//}
