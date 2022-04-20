#pragma once

#include "unclassified.h"
#include "rg_component_manager.h"


namespace PULSAR
{
	enum class RG_COMPONENT_TYPE
	{
		NONE,
		INPUT,
		SOURCE,
		PASS,
		RENDER_GRAPH
	};


	class RG_COMPONENT : public PULSAR::unclassified
	{
	private:
		friend class COMPONENT_MANAGER;

	protected:
		int		id = -1;
		bool	is_alloc = false;
		PULSAR::RG_COMPONENT_TYPE	type = PULSAR::RG_COMPONENT_TYPE::NONE;


		static RG_COMPONENT		*add_to_manager(RG_COMPONENT *rg_component)
		{
			rg_component->id = PULSAR::RG_COMPONENT_MANAGER::get_instance().add(rg_component);
			if (rg_component->id == -1)
			{
				delete rg_component;
				return (NULL);
			}
			rg_component->is_alloc = true;

			return (rg_component);
		}

	public:
		RG_COMPONENT(){ }
		~RG_COMPONENT()
		{
			this->destroy();
		}

		PULSAR::RG_COMPONENT_TYPE	get_type() const
		{
			return (this->type);
		}
		int		get_id() const
		{
			return (this->id);
		}

		void	destroy()
		{
			if (!this->is_alloc)
				return;
			this->is_alloc = false;

			PULSAR::RG_COMPONENT_MANAGER::get_instance().remove(this);
			delete this;
		}
	};
}
