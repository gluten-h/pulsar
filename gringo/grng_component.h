#pragma once

#include "grng_id3d.h"
#include "grng_exc_macros.h"
#include "grng_component_manager.h"


enum class GRNG_COMPONENT_TYPE
{
	NONE,
	CAMERA,
	MATERIAL,
	SKYBOX_MATERIAL,
};


class grng_component : public GRNG_ID3D
{
protected:
	int		id = -1;
	bool	is_alloc = false;
	GRNG_COMPONENT_TYPE		type = GRNG_COMPONENT_TYPE::NONE;

public:
	grng_component() : GRNG_ID3D(){ }
	~grng_component()
	{
		this->destroy();
	}

	void		destroy()
	{
		if (!this->is_alloc)
			return;
		this->is_alloc = false;

		GRNG_CM.remove_secure(this);
		delete this;
	}

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
