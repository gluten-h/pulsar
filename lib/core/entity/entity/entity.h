#pragma once

#include "pulsar_id3d.h"
#include "entity_manager.h"

#include <unordered_set>
#include <unordered_map>
#include <stdexcept>


namespace PULSAR
{
	enum class ENTITY_TYPE
	{
		NONE,
		OBJECT,
		POINT_LIGHT,
		DIR_LIGHT
	};


	class ENTITY : public PULSAR::PULSAR_ID3D
	{
	protected:
		int		id = -1;
		bool	is_alloc = false;
		PULSAR::ENTITY_TYPE		type = PULSAR::ENTITY_TYPE::NONE;

		std::unordered_map<int, int>	scene_local_id;			//	SCENE_ID TO LOCAL_ID


		static ENTITY		*add_to_manager(ENTITY *entity)
		{
			entity->id = PULSAR::ENTITY_MANAGER::get_instance().add(entity);
			if (entity->id == -1)
			{
				delete entity;
				return (NULL);
			}
			entity->is_alloc = true;

			return (entity);
		}

	public:
		ENTITY(const ENTITY &e) = delete;
		ENTITY(ENTITY &&e) = delete;
		ENTITY() : PULSAR::PULSAR_ID3D(){ }

		PULSAR::ENTITY_TYPE		get_type() const
		{
			return (this->type);
		}

		void	add_to_scene(int scene_id, int local_id)
		{
			this->scene_local_id[scene_id] = local_id;
		}
		void	remove_from_scene(int scene_id)
		{
			this->scene_local_id.erase(scene_id);
		}

		int		get_id() const
		{
			return (this->id);
		}
		int		get_local_id(int scene_id) const
		{
			try
			{
				return (this->scene_local_id.at(scene_id));
			}
			catch (const std::out_of_range &exc)
			{
				return (-1);
			}
		}
		const std::unordered_map<int, int>		&get_scene_local_id() const
		{
			return (this->scene_local_id);
		}

		virtual void	draw()
		{
		}
	};
}
