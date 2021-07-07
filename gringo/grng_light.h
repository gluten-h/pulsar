#pragma once

#include "igrng_d3d.h"
#include "grng_scene_def.h"


enum class GRNG_LIGHT_TYPE : int
{
	NONE = -1,
	POINT = 0,
	DIR = 1
};


typedef struct			grng_shader_light
{
	int					type;
	float				pd0[3];

	XMFLOAT3			pos;
	float				pd1[1];

	XMFLOAT3			dir;
	float				pd2[1];

	XMFLOAT3			color;
	float				pd3[1];

	XMFLOAT4			attenuation;
}						GRNG_SHADER_LIGHT;


typedef struct			grgn_shader_light_scene
{
	int					light_count;
	int					pd0[3];

	GRNG_SHADER_LIGHT	light[GRNG_MAX_LIGHT_COUNT];
}						GRNG_SHADER_LIGHT_SCENE;


class grng_light : public GRNG_ID3D
{
private:
	friend class grng_light_manager;

protected:
	GRNG_LIGHT_TYPE			type = GRNG_LIGHT_TYPE::NONE;
	int						id = -1;

public:
	grng_light(const grng_light &l) = delete;
	grng_light(grng_light &&l) = delete;
	grng_light() : GRNG_ID3D(){ }

	GRNG_LIGHT_TYPE			get_type() const
	{
		return (this->type);
	}

	int						get_id() const
	{
		return (this->id);
	}

	virtual void			set_shader_light(GRNG_SHADER_LIGHT &sl) = 0;
};

using GRNG_LIGHT = grng_light;
