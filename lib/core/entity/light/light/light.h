#pragma once

#include "entity.h"
#include "light_shader.h"
#include "light_manager.h"
#include "scene_manager.h"


namespace PULSAR
{
	enum class LIGHT_TYPE : int
	{
		NONE = -1,
		POINT = 0,
		DIR = 1
	};


	class LIGHT : public PULSAR::ENTITY
	{
	protected:
		PULSAR::LIGHT_TYPE		light_type = PULSAR::LIGHT_TYPE::NONE;


		static LIGHT	*add_to_manager(LIGHT *light)
		{
			light->id = PULSAR::LIGHT_MANAGER::get_instance().add(light);
			if (light->id == -1)
			{
				delete light;
				return (NULL);
			}
			light->is_alloc = true;

			return (light);
		}

	public:
		LIGHT(const LIGHT &l) = delete;
		LIGHT(LIGHT &&l) = delete;
		LIGHT() : PULSAR::ENTITY(){ }

		virtual void	set_shader_light(SHADER_LIGHT &sl) = 0;
	};
}
