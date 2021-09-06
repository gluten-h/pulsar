//#pragma once
//
//#include "rg_component.h"
//#include "def_render_graph.h"
//#include "rg_pass.h"
//#include "render_target.h"
//#include "depth_stencil_view.h"
//#include "exc_macros.h"
//
//#include <map>
//#include <unordered_map>
//#include <unordered_set>
//
//
//namespace PULSAR
//{
//	class RENDER_GRAPH : public PULSAR::RG_COMPONENT
//	{
//	private:
//		std::unordered_map<std::string, PULSAR::RG_SOURCE*>		global_sources;
//
//		std::unordered_map<std::string, RG_PASS *>				passes;
//		std::map<unsigned int, std::unordered_set<RG_PASS *>>	dependency_level_passes;
//
//		PULSAR::RG_BUFFER_SOURCE<PULSAR::RENDER_TARGET>			*backbuffer_source;
//		PULSAR::RG_BUFFER_SOURCE<PULSAR::DEPTH_STENCIL_VIEW>	*ds_view_source;
//
//	protected:
//		PULSAR::RENDER_TARGET			*backbuffer = NULL;
//		PULSAR::DEPTH_STENCIL_VIEW		*ds_view = NULL;
//
//	private:
//		void		link_pass(PULSAR::RG_PASS *pass)
//		{
//			for (auto &it : pass->get_inputs())
//			{
//				std::string source_name = it.second->get_source_name();
//				std::string source_pass_name = it.second->get_source_pass_name();
//
//				if (source_pass_name == RG_ROOT_STR)
//				{
//					try
//					{
//						it.second->bind(this->global_sources.at(source_name));
//					}
//					catch (const std::out_of_range &exc)
//					{
//						THROW_RG_EXC("RENDER_GRAPH: Global source " + source_name + " not found");
//					}
//				}
//				else
//				{
//					try
//					{
//						PULSAR::RG_PASS *source_pass = this->passes.at(source_pass_name);
//						it.second->bind(source_pass->get_source(source_name));
//					}
//					catch (const std::out_of_range &exc)
//					{
//						THROW_RG_EXC("RENDER_GRAPH: Pass " + source_pass_name + " not found");
//					}
//				}
//			}
//		}
//
//	public:
//		RENDER_GRAPH(PULSAR::RENDER_TARGET *backbuffer, PULSAR::DEPTH_STENCIL_VIEW *depth_stencil_view) : PULSAR::RG_COMPONENT()
//		{
//			this->type = PULSAR::RG_COMPONENT_TYPE::RENDER_GRAPH;
//
//			this->backbuffer = backbuffer;
//			this->ds_view = depth_stencil_view;
//
//			this->backbuffer_source = PULSAR::RG_BUFFER_SOURCE::create("backbuffer", this->backbuffer);
//			this->ds_view_source = PULSAR::RG_BUFFER_SOURCE::create("depth_stencil_view", this->ds_view);
//
//			this->register_global_source(this->backbuffer_source);
//			this->register_global_source(this->ds_view_source);
//		}
//		~RENDER_GRAPH()
//		{
//			this->backbuffer_source->destroy();
//			this->ds_view_source->destroy();
//		}
//
//		static PULSAR::RENDER_GRAPH		*create(RENDER_TARGET *backbuffer, DEPTH_STENCIL_VIEW *depth_stencil_view)
//		{
//			return ((PULSAR::RENDER_GRAPH*)RG_COMPONENT::add_to_manager(new RENDER_GRAPH(backbuffer, depth_stencil_view)));
//		}
//
//		void		register_global_source(PULSAR::RG_SOURCE *source)
//		{
//			std::string source_name = source->get_name();
//			try
//			{
//				this->global_sources.at(source_name);
//				THROW_RG_EXC("RENDER_GRAPH: Global source " + source_name + " already exists");
//			}
//			catch (const std::out_of_range &exc){ }
//
//			this->global_sources[source_name] = source;
//		}
//
//		void		add_pass(RG_PASS *pass, unsigned int dependency_level)
//		{
//			if (!pass)
//				THROW_RG_EXC("RENDER_GRAPH: Pass is NULL");
//
//			std::string pass_name = pass->get_name();
//			try
//			{
//				this->passes.at(pass_name);
//				THROW_RG_EXC("RENDER_GRAPH: Pass " + pass_name + " already exists");
//			}
//			catch (const std::out_of_range &exc){ }
//
//			//this->link_pass(pass);
//			pass->set_dependency_level(dependency_level);
//
//			this->passes[pass_name] = pass;
//			this->dependency_level_passes[dependency_level].insert(pass);
//		}
//
//		void		compile()
//		{
//			for (auto &p : this->passes)
//				this->link_pass(p.second);
//		}
//
//		void		validate() const
//		{
//			for (auto &p : this->passes)
//				p.second->validate();
//		}
//
//		void		execute()
//		{
//			//for (auto &p : this->passes)
//			//	p.second->execute();
//
//			for (auto &dl : this->dependency_level_passes)
//			{
//				for (auto &p : dl.second)
//					p->execute();
//			}
//		}
//	};
//}
