#pragma once

#include "grng_def_render_graph.h"
#include "grng_rg_pass.h"
#include "grng_render_target.h"
#include "grng_depth_stencil_view.h"

#include <map>
#include <unordered_map>
#include <unordered_set>


class grng_render_graph
{
private:
	std::unordered_map<std::string, GRNG_RG_SOURCE*>	global_sources;

	std::unordered_map<std::string, GRNG_RG_PASS*>				passes;
	std::map<unsigned int, std::unordered_set<GRNG_RG_PASS*>>	dependency_level_passes;

	GRNG_RENDER_TARGET			*render_target = NULL;
	GRNG_DEPTH_STENCIL_VIEW		*depth_stencil_view = NULL;

	GRNG_RG_BUFFER_SOURCE<GRNG_RENDER_TARGET>			rt_source;// = GRNG_RG_BUFFER_SOURCE<GRNG_RENDER_TARGET>("backbuffer");
	GRNG_RG_BUFFER_SOURCE<GRNG_DEPTH_STENCIL_VIEW>		ds_view_source;// = GRNG_RG_BUFFER_SOURCE<GRNG_DEPTH_STENCIL_VIEW>("depth_stencil_view");



	void		link_pass(GRNG_RG_PASS &pass)
	{
		for (auto &it : pass.get_inputs())
		{
			std::string source_name = it.second->get_source_name();
			std::string source_pass_name = it.second->get_source_pass_name();

			if (source_pass_name == GRNG_RG_ROOT_STR)
			{
				try
				{
					it.second->bind(this->global_sources.at(source_name));
				}
				catch (const std::out_of_range &exc)
				{
					GRNG_THROW_RG_EXC("GRNG_RENDER_GRAPH: Global source " + source_name + " not found");
				}
			}
			else
			{
				try
				{
					GRNG_RG_PASS *source_pass = this->passes.at(source_pass_name);
					it.second->bind(&source_pass->get_source(source_name));
				}
				catch (const std::out_of_range &exc)
				{
					GRNG_THROW_RG_EXC("GRNG_RENDER_GRAPH: Pass " + source_pass_name + " not found");
				}
			}
		}
		pass.set_linked();
	}

public:
	void		set(const GRNG_RENDER_TARGET &render_target, const GRNG_DEPTH_STENCIL_VIEW &depth_stencil_view)
	{
		this->render_target = (GRNG_RENDER_TARGET*)&render_target;
		this->depth_stencil_view = (GRNG_DEPTH_STENCIL_VIEW*)&depth_stencil_view;

		this->rt_source = GRNG_RG_BUFFER_SOURCE<GRNG_RENDER_TARGET>("backbuffer", this->render_target);
		this->ds_view_source = GRNG_RG_BUFFER_SOURCE<GRNG_DEPTH_STENCIL_VIEW>("depth_stencil_view", this->depth_stencil_view);

		this->register_global_source(this->rt_source);
		this->register_global_source(this->ds_view_source);
	}

	void		register_global_source(const GRNG_RG_SOURCE &source)
	{
		std::string source_name = source.get_name();
		try
		{
			this->global_sources.at(source_name);
			GRNG_THROW_RG_EXC("GRNG_RENDER_GRAPH: Global source " + source_name + " already exists");
		}
		catch (const std::out_of_range &exc){ }

		this->global_sources[source_name] = (GRNG_RG_SOURCE*)&source;
	}

	void		add_pass(GRNG_RG_PASS &pass, unsigned int dependency_level)
	{
		std::string pass_name = pass.get_name();
		try
		{
			this->passes.at(pass_name);
			GRNG_THROW_RG_EXC("GRNG_RENDER_GRAPH: Pass " + pass_name + " already exists");
		}
		catch (const std::out_of_range &exc){ }

		//this->link_pass(pass);
		pass.set_dependency_level(dependency_level);

		this->passes[pass_name] = (GRNG_RG_PASS*)&pass;
		this->dependency_level_passes[dependency_level].insert((GRNG_RG_PASS*)&pass);
	}

	void		compile()
	{
		for (auto &p : this->passes)
			this->link_pass(*p.second);
	}

	void		validate() const
	{
		for (auto &p : this->passes)
			p.second->validate();
	}

	void		execute()
	{
		//for (auto &p : this->passes)
		//	p.second->execute();

		for (auto &dl : this->dependency_level_passes)
		{
			for (auto &p : dl.second)
				p->execute();
		}
	}
};

using GRNG_RENDER_GRAPH = grng_render_graph;
