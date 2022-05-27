
#include "render_graph.h"
#include "pass.h"
#include "input.h"
#include "source.h"
#include "exceptions/rg_exception.h"
#include "rg_const.h"


pulsar::rg::render_graph::render_graph()
{
	this->m_passes.resize(pulsar::rg::MAX_PASS_LEVELS);
}

void	pulsar::rg::render_graph::register_global_source(pulsar::rg::source *source)
{
	const std::string &name = source->name();
	if (this->m_global_sources.find(name) != this->m_global_sources.end())
		THROW_RG_EXC("Global source \'" + name + "\' already exists");

	this->m_global_sources[name] = source;
}

void	pulsar::rg::render_graph::add_pass(uint32_t level, pulsar::rg::pass *pass)
{
	if (level >= pulsar::rg::MAX_PASS_LEVELS)
		THROW_RG_EXC("Dependency levels overflow");

	const std::string &name = pass->name();
	if (this->m_passes_reg.find(name) != this->m_passes_reg.end())
		THROW_RG_EXC("Pass \'" + name + "\' already exists");

	this->m_passes_reg[name] = pass;
	this->m_passes[level].push_back(pass);
}

void	pulsar::rg::render_graph::link_pass(pulsar::rg::pass *pass)
{
	for (auto &[input_name, input] : pass->get_all_inputs())
	{
		const std::string source_name = input->source_name();
		const std::string source_pass_name = input->source_pass_name();

		if (source_pass_name.empty())
			THROW_RG_EXC("Source pass name of input " + input_name + " is undefined");
		if (source_name.empty())
			THROW_RG_EXC("Source name of input " + input_name + " is undefined");

		if (source_pass_name == pulsar::rg::RG_ROOT)
		{
			auto source_it = this->m_global_sources.find(source_name);
			if (source_it == this->m_global_sources.end())
				THROW_RG_EXC("Global source " + source_name + " does not exist");

			pulsar::rg::source *source = source_it->second;
			input->bind(source);
		}
		else
		{
			auto source_pass_it = this->m_passes_reg.find(source_pass_name);
			if (source_pass_it == this->m_passes_reg.end())
				THROW_RG_EXC("Source pass " + source_pass_name + " does not exist");

			pulsar::rg::source *source = source_pass_it->second->get_source(source_name);
			input->bind(source);
		}
	}
}

void	pulsar::rg::render_graph::compile()
{
	for (auto &level : this->m_passes)
	{
		for (auto *pass : level)
			this->link_pass(pass);
	}
}

void	pulsar::rg::render_graph::validate() const
{
	for (auto &level : this->m_passes)
	{
		for (auto *pass : level)
			pass->validate();
	}
}

void	pulsar::rg::render_graph::execute()
{
	for (auto &level : this->m_passes)
	{
		for (auto *pass : level)
			pass->execute();
	}
}