#pragma once

#include "grng_id3d.h"
#include "grng_const_buffers.h"
#include "grng_bindable.h"
#include "grng_transform_shader.h"

#include <vector>
#include <unordered_set>


enum class GRNG_ENTITY_TYPE
{
	NONE,
	OBJECT
};


class grng_entity : public GRNG_ID3D
{
private:
	friend class grng_entity_manager;
	friend class grng_bindable_manager;
	friend class grng_scene;

protected:
	GRNG_ENTITY_TYPE				type = GRNG_ENTITY_TYPE::NONE;
	int								id = -1;
	int								scene_id = -1;

	std::unordered_set<GRNG_BINDABLE*>		bindables;

	GRNG_SHADER_TRANSFORM									vert_transform;
	static GRNG_VERT_CONST_BUFFER<GRNG_SHADER_TRANSFORM>	transform_cbuffer;


	void		erase_bindable(GRNG_BINDABLE &bindable)
	{
		this->bindables.erase(&bindable);
	}

public:
	grng_entity(const grng_entity &e) = delete;
	grng_entity(grng_entity &&e) = delete;
	grng_entity() : GRNG_ID3D(){ }

	GRNG_ENTITY_TYPE		get_type() const
	{
		return (this->type);
	}

	int						get_id() const
	{
		return (this->id);
	}


	void	add_bindable(GRNG_BINDABLE &bindable)
	{
		bindable.entity_scene_map[this->id] = this->scene_id;
		this->bindables.insert(&bindable);
	}

	void	remove_bindable(GRNG_BINDABLE &bindable)
	{
		bindable.entity_scene_map.erase(this->id);
		this->erase_bindable(bindable);
	}

	virtual void				draw() = 0;
};

using GRNG_ENTITY = grng_entity;
