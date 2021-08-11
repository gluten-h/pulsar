#pragma once

#include "grng_id3d.h"
#include "grng_entity_manager.h"

#include <unordered_set>
#include <unordered_map>


enum class GRNG_ENTITY_TYPE
{
	NONE,
	OBJECT,
	POINT_LIGHT,
	DIR_LIGHT
};


class grng_entity : public GRNG_ID3D
{
protected:
	int					id = -1;
	bool				is_alloc = false;
	GRNG_ENTITY_TYPE	type = GRNG_ENTITY_TYPE::NONE;

	std::unordered_map<int, int>	scene_local_id;			//	SCENE_ID TO LOCAL_ID

public:
	grng_entity(const grng_entity &e) = delete;
	grng_entity(grng_entity &&e) = delete;
	grng_entity() : GRNG_ID3D(){ }

	GRNG_ENTITY_TYPE	get_type() const
	{
		return (this->type);
	}

	void		add_to_scene(int scene_id, int local_id)
	{
		this->scene_local_id[scene_id] = local_id;
	}
	void		remove_from_scene(int scene_id)
	{
		this->scene_local_id.erase(scene_id);
	}

	int			get_id() const
	{
		return (this->id);
	}
	int			get_local_id(int scene_id) const
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

	virtual void	draw(){ }
};

using GRNG_ENTITY = grng_entity;
