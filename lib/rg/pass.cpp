
#include "pass.h"
#include "input.h"
#include "source.h"
#include "utils/pulsar_utils.h"
#include "exceptions/rg_exception.h"
#include "rg_const.h"


PULSAR::rg::pass::pass(const std::string &name)
{
	this->m_name = name;
}

PULSAR::rg::input	*PULSAR::rg::pass::get_input(const std::string &input_name)
{
	if (this->m_inputs.find(input_name) == this->m_inputs.end())
		THROW_RG_EXC("Input \'" + input_name + "\' does not exist in pass " + this->name());

	return (this->m_inputs[input_name]);
}

PULSAR::rg::source	*PULSAR::rg::pass::get_source(const std::string &source_name)
{
	if (this->m_sources.find(source_name) == this->m_sources.end())
		THROW_RG_EXC("Source \'" + source_name + "\' does not exist in pass " + this->name());

	return (this->m_sources[source_name]);
}

std::unordered_map<std::string, PULSAR::rg::input*>		&PULSAR::rg::pass::get_all_inputs()
{
	return (this->m_inputs);
}

const std::string	&PULSAR::rg::pass::name() const
{
	return (this->m_name);
}

void	PULSAR::rg::pass::register_input(PULSAR::rg::input *input)
{
	const std::string &name = input->name();
	if (this->m_inputs.find(name) != this->m_inputs.end())
		THROW_RG_EXC("Input \'" + name + "\' already exists in pass " + this->name());

	this->m_inputs[name] = input;
}

void	PULSAR::rg::pass::register_source(PULSAR::rg::source *source)
{
	const std::string &name = source->name();
	if (this->m_sources.find(name) != this->m_sources.end())
		THROW_RG_EXC("Source \'" + name + "\' already exists in pass " + this->name());

	this->m_sources[name] = source;
}

void	PULSAR::rg::pass::link_input(const std::string &input_name, const std::string &source_path)
{
	PULSAR::rg::input *input = this->get_input(input_name);
	std::vector<std::string> split = PULSAR::utils::str_split(source_path, PULSAR::rg::RG_PATH_DELIM);
	if (split.size() != 2ull)
		THROW_RG_EXC("Invalid source path format");

	input->set_source(split[0], split[1]);
}

void	PULSAR::rg::pass::validate() const
{
	for (auto &[key, input] : this->m_inputs)
		input->validate();
	for (auto &[key, source] : this->m_sources)
		source->validate();
}
