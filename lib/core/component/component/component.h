#pragma once

#include "pulsar_id3d.h"
#include "exc_macros.h"
#include "component_manager.h"


namespace PULSAR
{
	enum class COMPONENT_TYPE
	{
		NONE,
		CAMERA,
		MATERIAL,
		SKYBOX_MATERIAL,
	};


	class COMPONENT : public PULSAR::PULSAR_ID3D
	{
	protected:
		int		id = -1;
		bool	is_alloc = false;
		COMPONENT_TYPE		type = COMPONENT_TYPE::NONE;


		static COMPONENT	*add_to_manager(COMPONENT *component)
		{
			component->id = CM.add(component);
			if (component->id == -1)
			{
				delete component;
				return (NULL);
			}
			component->is_alloc = true;

			return (component);
		}

	public:
		COMPONENT() : PULSAR::PULSAR_ID3D(){ }
		~COMPONENT()
		{
			this->destroy();
		}

		void	destroy()
		{
			if (!this->is_alloc)
				return;
			this->is_alloc = false;

			PULSAR::CM.remove_secure(this);
			delete this;
		}

		COMPONENT_TYPE		get_type() const
		{
			return (this->type);
		}
		int		get_id() const
		{
			return (this->id);
		}
	};
}
