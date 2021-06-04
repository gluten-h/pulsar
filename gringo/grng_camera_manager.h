#pragma once

#include "grng_manager.h"
#include "grng_camera.h"
#include "grng_scene_def.h"


class grng_camera_manager : public GRNG_MANAGER<GRNG_CAMERA, GRNG_MAX_CAMERA_COUNT>
{
private:
	void		add_event(int added_id) override{ }
	void		remove_event(int removed_id) override{ }

public:
	grng_camera_manager() : GRNG_MANAGER<GRNG_CAMERA, GRNG_MAX_CAMERA_COUNT>(){ }

	void		bind() override{ }
};

using GRNG_CAMERA_MANAGER = grng_camera_manager;
