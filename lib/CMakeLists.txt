
cmake_minimum_required(VERSION 3.20)

set(LIB_SOURCES	
						dcb/baked_layout.cpp
						dcb/buffer.cpp
						dcb/buffer_data.cpp
						dcb/layout_elem.cpp
						dcb/layout_elem_memory.cpp
						dcb/raw_layout.cpp


						exceptions/base_exception.cpp
						exceptions/gfx_exception.cpp
						exceptions/rg_exception.cpp
						exceptions/win_exception.cpp


						gfx/gfx.cpp


						gfx_resources/texture_resource.cpp
						gfx_resources/depth_stencil_view.cpp
						gfx_resources/shader_texture.cpp
						gfx_resources/render_texture.cpp
						gfx_resources/cubemap.cpp
						gfx_resources/framebuffer.cpp
						gfx_resources/buffer_resource.cpp
						gfx_resources/index_buffer.cpp
						gfx_resources/shader.cpp
						gfx_resources/vert_shader.cpp
						gfx_resources/geom_shader.cpp
						gfx_resources/frag_shader.cpp
						gfx_resources/depth_stencil_state.cpp
						gfx_resources/input_layout.cpp
						gfx_resources/rasterizer_state.cpp
						gfx_resources/sampler.cpp
						gfx_resources/viewport.cpp
						gfx_resources/dynamic_cbuffer.cpp
						gfx_resources/vert_dynamic_cbuffer.cpp
						gfx_resources/frag_dynamic_cbuffer.cpp
						gfx_resources/sync_resource.cpp


						input/pulsar_input.cpp
						input/pulsar_input_mouse.cpp
						input/pulsar_input_keyboard.cpp


						render_queue/render_queue.cpp
						render_queue/job.cpp


						render_graph/render_graph.cpp
						render_graph/pass.cpp
						render_graph/input.cpp
						render_graph/source.cpp


						utils/math.cpp
						utils/utils.cpp
						utils/shader_include.cpp


						window/window.cpp
						window/window_proc.cpp
						window/window_data.cpp)
set(LIB_SOURCES ${LIB_SOURCES} PARENT_SCOPE)


set(LIB_INCLUDES		
						dcb/dcb.h
						dcb/types.h
						dcb/layout_elem.h
						dcb/layout.h
						dcb/raw_layout.h
						dcb/baked_layout.h
						dcb/layout_elem_ref.h
						dcb/buffer.h


						ecs/entt/entt.h
						ecs/types.h
						ecs/system.h
						ecs/ecs.h


						exceptions/base_exception.h
						exceptions/gfx_exception.h
						exceptions/rg_exception.h
						exceptions/win_exception.h
						exceptions/exceptions.h


						filesystem/filesystem.h


						gfx/gfx.h


						gfx_resources/gfx_resources.h
						gfx_resources/texture_resource.h
						gfx_resources/shader_texture.h
						gfx_resources/depth_stencil_view.h
						gfx_resources/render_texture.h
						gfx_resources/cubemap.h
						gfx_resources/framebuffer.h
						gfx_resources/buffer_resource.h
						gfx_resources/vertex_buffer.h
						gfx_resources/index_buffer.h
						gfx_resources/cbuffer.h
						gfx_resources/vert_cbuffer.h
						gfx_resources/frag_cbuffer.h
						gfx_resources/shader.h
						gfx_resources/vert_shader.h
						gfx_resources/geom_shader.h
						gfx_resources/frag_shader.h
						gfx_resources/depth_stencil_state.h
						gfx_resources/input_layout.h
						gfx_resources/rasterizer_state.h
						gfx_resources/sampler.h
						gfx_resources/viewport.h
						gfx_resources/dynamic_cbuffer.h
						gfx_resources/vert_dynamic_cbuffer.h
						gfx_resources/frag_dynamic_cbuffer.h
						gfx_resources/sync_resource.h

						gfx_resources/bind_group/rtv_bind_group.h
						gfx_resources/bind_group/srv_bind_group.h
						gfx_resources/bind_group/sampler_bind_group.h
						gfx_resources/bind_group/viewport_bind_group.h
						gfx_resources/bind_group/cbuffer_bind_group.h
						gfx_resources/bind_group/vert_cbuffer_bind_group.h
						gfx_resources/bind_group/frag_cbuffer_bind_group.h


						input/pulsar_keycodes.h
						input/pulsar_mousecodes.h
						input/pulsar_input.h


						render_queue/types.h
						render_queue/render_queue.h
						render_queue/job.h


						render_graph/rg_const.h
						render_graph/render_graph.h
						render_graph/pass.h
						render_graph/input.h
						render_graph/sync_input.h
						render_graph/async_input.h
						render_graph/source.h
						render_graph/sync_source.h
						render_graph/async_source.h


						utils/math.h
						utils/utils.h
						utils/singleton.h
						utils/shader_include.h


						window/window.h)
set(LIB_INCLUDES ${LIB_INCLUDES} PARENT_SCOPE)


set(LIB_INCLUDE_DIRS	
						#bindables
						./)

target_sources(${PROJECT_NAME} PUBLIC ${LIB_SOURCES} ${LIB_INCLUDES})
target_include_directories(${PROJECT_NAME} PUBLIC ${LIB_INCLUDE_DIRS})
