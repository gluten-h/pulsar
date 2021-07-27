#pragma once

#include "grng_id3d.h"
#include "grng_exc_macros.h"


enum class GRNG_COMPONENT_TYPE
{
	NONE,
	CAMERA,
	MATERIAL,
	SKYBOX_MATERIAL,
	MESH
};


class grng_component : public GRNG_ID3D
{
private:
	friend class grng_component_manager;

protected:
	GRNG_COMPONENT_TYPE			type = GRNG_COMPONENT_TYPE::NONE;
	int							id = -1;

public:
	grng_component() : GRNG_ID3D(){ }

	GRNG_COMPONENT_TYPE			get_type() const
	{
		return (this->type);
	}

	int							get_id() const
	{
		return (this->id);
	}
};

using GRNG_COMPONENT = grng_component;
