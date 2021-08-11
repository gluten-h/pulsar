#pragma once

#include "grng_entity.h"
#include "grng_light_shader.h"
#include "grng_light_manager.h"
#include "grng_scene_manager.h"


enum class GRNG_LIGHT_TYPE : int
{
	NONE = -1,
	POINT = 0,
	DIR = 1
};


class grng_light : public GRNG_ENTITY
{
protected:
	GRNG_LIGHT_TYPE			light_type = GRNG_LIGHT_TYPE::NONE;

public:
	grng_light(const grng_light &l) = delete;
	grng_light(grng_light &&l) = delete;
	grng_light() : GRNG_ENTITY(){ }

	virtual void		set_shader_light(GRNG_SHADER_LIGHT &sl) = 0;
};

using GRNG_LIGHT = grng_light;
