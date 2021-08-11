#pragma once

#include "grng_id3d.h"


enum class GRNG_RG_COMPONENT_TYPE
{
	NONE,
	INPUT,
	SOURCE,
	PASS
};


class grng_rg_component : public GRNG_ID3D
{
private:
	friend class grng_component_manager;

protected:
	GRNG_RG_COMPONENT_TYPE		type = GRNG_RG_COMPONENT_TYPE::NONE;
	int							id = -1;

public:
	grng_rg_component() : GRNG_ID3D(){ }

	GRNG_RG_COMPONENT_TYPE		get_type() const
	{
		return (this->type);
	}
	int							get_id() const
	{
		return (this->id);
	}
};

using GRNG_RG_COMPONENT = grng_rg_component;
