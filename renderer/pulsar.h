#pragma once

#include "bindables.h"
#include "components.h"
#include "gfx/gfx.h"
#include "render_queue/render_queue.h"
#include "renderer/renderer.h"
#include "config/pulsar_config.h"
#include "components/components.h"
//#include "pulsar_input.h"
#include "node/node.h"
#include "scene/scene.h"
#include "exceptions/exceptions.h"
#include "utils/math.h"
#include "window/window.h"
#include "pulsar_render_graph/deferred_render_graph.h"


namespace pulsar
{
	void	init(HINSTANCE h_instance)
	{
		pulsar::window::init(h_instance);
		
		// singletons init
		pulsar::gfx::instance();
		pulsar::render_queue::instance();
		pulsar::renderer::instance();
	}

	void	terminate()
	{

	}
}
