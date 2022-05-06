#pragma once

#include "bindables.h"
#include "components.h"
#include "entities.h"
#include "gfx.h"
#include "_gfx/_gfx.h"
#include "pulsar_input.h"
#include "pulsar_resource_manager.h"
#include "rg_components.h"
#include "scene.h"
#include "def/pulsar_def.h"
#include "exceptions/pulsar_exc.h"
#include "utils/pulsar_math.h"
#include "window/window.h"


namespace PULSAR
{
	void	init(HINSTANCE h_instance)
	{
		PULSAR::window::init(h_instance);
	}

	void	terminate()
	{
		
	}
}
