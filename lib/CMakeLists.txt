
cmake_minimum_required(VERSION 3.20)

set(LIB_SOURCES	
						bindables/bindable/buffer_resource.cpp
						bindables/cubemap/cubemap_data.cpp
						bindables/cubemap/cubemap_dds.cpp
						bindables/cubemap/cubemap.cpp
						bindables/depth_stencil/depth_stencil_state_data.cpp
						bindables/depth_stencil/depth_stencil_state.cpp
						bindables/depth_stencil/depth_stencil_view_data.cpp
						bindables/depth_stencil/depth_stencil_view.cpp
						bindables/dynamic_const_buffers/dynamic_const_buffer.cpp
						bindables/dynamic_const_buffers/dynamic_const_buffer_data.cpp
						bindables/dynamic_const_buffers/frag_dynamic_const_buffer.cpp
						bindables/dynamic_const_buffers/vert_dynamic_const_buffer.cpp
						bindables/input_layout/input_layout_data.cpp
						bindables/input_layout/input_layout.cpp
						bindables/rasterizer_state/rasterizer_state_data.cpp
						bindables/rasterizer_state/rasterizer_state.cpp
						bindables/framebuffer/framebuffer_data.cpp
						bindables/framebuffer/framebuffer.cpp
						bindables/render_texture/render_texture_data.cpp
						bindables/render_texture/render_texture.cpp
						bindables/sampler/sampler_data.cpp
						bindables/sampler/sampler.cpp
						bindables/shaders/frag_shader_data.cpp
						bindables/shaders/frag_shader.cpp
						bindables/shaders/geom_shader_data.cpp
						bindables/shaders/geom_shader.cpp
						bindables/shaders/shader_data.cpp
						bindables/shaders/vert_shader_data.cpp
						bindables/shaders/vert_shader.cpp
						bindables/shader_texture/shader_texture_data.cpp
						bindables/shader_texture/shader_texture.cpp
						bindables/viewport/viewport_data.cpp
						bindables/viewport/viewport.cpp


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


						input/pulsar_input.cpp


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
						containers/sparse_set.h


						bindables/bindable/bindable.h
						bindables/bindable/buffer_resource.h
						bindables/const_buffers/const_buffer.h
						bindables/const_buffers/frag_const_buffer.h
						bindables/const_buffers/vert_const_buffer.h
						bindables/cubemap/cubemap.h
						bindables/depth_stencil/depth_stencil_state.h
						bindables/depth_stencil/depth_stencil_view.h
						bindables/dynamic_const_buffers/dynamic_const_buffer.h
						bindables/dynamic_const_buffers/frag_dynamic_const_buffer.h
						bindables/dynamic_const_buffers/vert_dynamic_const_buffer.h
						bindables/input_layout/input_layout.h
						bindables/rasterizer_state/rasterizer_state.h
						bindables/framebuffer/framebuffer.h
						bindables/render_texture/render_texture.h
						bindables/sampler/sampler.h
						bindables/shaders/frag_shader.h
						bindables/shaders/geom_shader.h
						bindables/shaders/shader.h
						bindables/shaders/vert_shader.h
						bindables/shader_texture/shader_texture.h
						bindables/viewport/viewport.h
						bindables/bindables.h


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
						render_graph/buffer_input.h
						render_graph/bindable_input.h
						render_graph/source.h
						render_graph/buffer_source.h
						render_graph/bindable_source.h


						utils/math.h
						utils/utils.h
						utils/singleton.h
						utils/shader_include.h


						window/window.h)
set(LIB_INCLUDES ${LIB_INCLUDES} PARENT_SCOPE)


set(LIB_INCLUDE_DIRS	
						containers
						bindables
						./)

target_sources(${PROJECT_NAME} PUBLIC ${LIB_SOURCES} ${LIB_INCLUDES})
target_include_directories(${PROJECT_NAME} PUBLIC ${LIB_INCLUDE_DIRS})
