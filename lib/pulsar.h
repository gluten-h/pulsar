#pragma once

#include "bindables.h"
//#include "components.h"
#include "entities.h"
#include "gfx.h"
#include "_gfx/_gfx.h"
#include "pulsar_input.h"
//#include "pulsar_resource_manager.h"
//#include "rg_components.h"
#include "node/node.h"
#include "scene/scene.h"
#include "config/pulsar.h"
#include "exceptions/exceptions.h"
#include "utils/math.h"
#include "window/window.h"
#include "render_graph/pulsar_render_graph.h"


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
