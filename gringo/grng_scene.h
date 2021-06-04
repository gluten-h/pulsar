#pragma once

#include "grng_light_manager.h"
#include "grng_drawable_manager.h"


class grng_scene
{
private:
	GRNG_LIGHT_MANAGER		light_manager;
	GRNG_DRAWABLE_MANAGER	drawable_manager;

public:
	int				add_light(GRNG_LIGHT &light)
	{
		return (this->light_manager.add(light));
	}

	void			remove_light(unsigned int id)
	{
		this->light_manager.remove_secure(id);
	}

	void			remove_light(GRNG_LIGHT &light)
	{
		this->light_manager.remove_secure(light);
	}

	GRNG_LIGHT		*get_light(unsigned int id)
	{
		return (this->light_manager.get_data_secure(id));
	}


	int				add_drawable(GRNG_DRAWABLE &drawable)
	{
		return (this->drawable_manager.add(drawable));
	}

	void			remove_drawable(unsigned int id)
	{
		this->drawable_manager.remove_secure(id);
	}

	void			remove_drawable(GRNG_DRAWABLE &drawable)
	{
		this->drawable_manager.remove_secure(drawable);
	}

	GRNG_DRAWABLE	*get_drawable(unsigned int id)
	{
		return (this->drawable_manager.get_data_secure(id));
	}


	void			draw()
	{
		this->drawable_manager.draw();
	}

	void			bind()
	{
		this->light_manager.bind();
	}
};

using GRNG_SCENE = grng_scene;
