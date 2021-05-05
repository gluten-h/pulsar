#pragma once

#include "grng_d3d.h"
#include "grng_bindable.h"


enum class GRNG_ASSET_TYPE
{
	GRNG_UNSPECIFIED,
	GRNG_MESH,
	GRNG_TEXTURE,
};


class grng_asset : public GRNG_BINDABLE
{
protected:
	GRNG_ASSET_TYPE		type = GRNG_ASSET_TYPE::GRNG_UNSPECIFIED;

public:
	grng_asset(const grng_asset &a) = delete;
	grng_asset(grng_asset &&a) = delete;
	grng_asset() : GRNG_BINDABLE()
	{
		
	}

	virtual void		create_buffer() = 0;
};


using GRNG_ASSET = grng_asset;
