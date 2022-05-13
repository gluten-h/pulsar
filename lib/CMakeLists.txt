
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
						bindables/mesh/mesh_d3d.cpp
						bindables/mesh/mesh_data.cpp
						bindables/mesh/mesh_obj.cpp
						bindables/mesh/mesh.cpp
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

						core/component/camera/camera/camera_data.cpp
						core/component/camera/camera/camera_def.cpp
						core/component/camera/camera/camera_get.cpp
						core/component/camera/camera/camera_update.cpp
						core/component/camera/camera/camera.cpp
						core/component/material/material/material_props.cpp
						core/component/skybox_material/skybox_material/skybox_material.cpp

						core/entity/light/dir/dir_light_data.cpp
						core/entity/light/dir/dir_light_get.cpp
						core/entity/light/dir/dir_light.cpp
						core/entity/light/point/point_light_data.cpp
						core/entity/light/point/point_light_get.cpp
						core/entity/light/point/point_light.cpp
						core/entity/object/object.cpp

						core/gfx/gfx.cpp

						core/input/mouse/pulsar_mouse_button.cpp
						core/input/mouse/pulsar_mouse.cpp

						core/misc/skybox/skybox_data.cpp
						core/misc/skybox/skybox_def.cpp
						core/misc/skybox/skybox.cpp
						core/misc/texture2d/texture2d_data.cpp
						core/misc/texture2d/texture2d.cpp
						core/misc/transform/transform/transform.cpp


						core/resource_manager/pulsar_resource_manager.cpp


						dcb/baked_layout.cpp
						dcb/buffer.cpp
						dcb/buffer_data.cpp
						dcb/layout_elem.cpp
						dcb/layout_elem_memory.cpp
						dcb/raw_layout.cpp


						ecs/entity_bin_tree_array.cpp
						ecs/types.cpp


						exceptions/base_exception.cpp
						exceptions/gfx_exception.cpp
						exceptions/rg_exception.cpp
						exceptions/win_exception.cpp


						_gfx/_gfx.cpp


						rg/render_graph.cpp
						rg/pass.cpp
						rg/input.cpp
						rg/source.cpp


						utils/math.cpp
						utils/utils.cpp
						utils/shader_include.cpp


						window/window_cursor.cpp
						window/window_draw.cpp
						window/window_update.cpp
						window/window.cpp
						window/window_proc.cpp
						window/window_data.cpp)
set(LIB_SOURCES ${LIB_SOURCES} PARENT_SCOPE)


set(LIB_INCLUDES		
						containers/manager.h
						containers/fixed_vector.h
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
						bindables/mesh/mesh.h
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

						core/component/camera/camera/camera.h
						core/component/camera/camera_shader/camera_deferred_shader.h
						core/component/camera/camera_shader/camera_post_effects_shader.h
						core/component/component/component.h
						core/component/material/material/material.h
						core/component/material/material_const.h
						core/component/skybox_material/skybox_material/skybox_material.h
						core/component/skybox_material/skybox_material_def.h
						core/component/skybox_material/skybox_material_shader.h
						core/component/components.h

						core/entity/entity/bindable_entity.h
						core/entity/entity/entity.h
						core/entity/light/dir/dir_light.h
						core/entity/light/light/light_shader.h
						core/entity/light/light/light.h
						core/entity/light/point/point_light.h
						core/entity/light/lights.h
						core/entity/object/object.h
						core/entity/entities.h

						core/filesystem/filesystem.h

						core/gfx/gfx.h

						core/input/mouse/pulsar_mouse.h
						core/input/pulsar_input.h

						core/misc/skybox/skybox.h
						core/misc/texture2d/texture2d.h
						core/misc/transform/transform/transform.h
						core/misc/transform/transform_shader.h

						core/resource_manager/pulsar_resource_manager.h

						#core/render_queue/render_queue.h

						core/rg_component/render_graph/render_graph.h
						core/rg_component/rg_component/rg_component.h
						core/rg_component/rg_input/rg_bindable_input.h
						core/rg_component/rg_input/rg_buffer_input.h
						core/rg_component/rg_input/rg_input.h
						core/rg_component/rg_input/rg_inputs.h
						core/rg_component/rg_pass/rg_pass.h
						core/rg_component/rg_source/rg_bindable_source.h
						core/rg_component/rg_source/rg_buffer_source.h
						core/rg_component/rg_source/rg_source.h
						core/rg_component/rg_source/rg_sources.h
						core/rg_component/rg_components.h


						dcb/dcb.h
						dcb/types.h
						dcb/layout_elem.h
						dcb/layout.h
						dcb/raw_layout.h
						dcb/baked_layout.h
						dcb/layout_elem_ref.h
						dcb/buffer.h


						ecs/types.h
						ecs/registry.h
						ecs/entity_bin_tree_array.h
						ecs/system.h
						ecs/ecs.h


						exceptions/base_exception.h
						exceptions/gfx_exception.h
						exceptions/rg_exception.h
						exceptions/win_exception.h
						exceptions/exceptions.h


						_gfx/_gfx.h


						rg/rg_const.h
						rg/render_graph.h
						rg/pass.h
						rg/input.h
						rg/buffer_input.h
						rg/bindable_input.h
						rg/source.h
						rg/buffer_source.h
						rg/bindable_source.h


						utils/math.h
						utils/utils.h
						utils/singleton.h
						utils/shader_include.h


						window/window.h


						pulsar.h)
set(LIB_INCLUDES ${LIB_INCLUDES} PARENT_SCOPE)


set(LIB_INCLUDE_DIRS	
						containers


						bindables

						#core/component/camera/camera
						c#ore/component/camera/camera_shader
						#core/component/component
						#core/component/material/material
						#core/component/material
						#core/component/skybox_material/skybox_material
						#core/component/skybox_material
						#core/component

						core/entity/entity
						core/entity/light/dir
						core/entity/light/light
						core/entity/light/point
						core/entity/light
						core/entity/object
						core/entity

						core/gfx

						core/input/mouse
						core/input

						#core/misc/shader_include
						#core/misc/skybox
						#core/misc/texture2d
						#core/misc/transform/transform
						#core/misc/transform

						core/resource_manager

						core/render_queue

						core/scene


						core


						./)

target_sources(${PROJECT_NAME} PUBLIC ${LIB_SOURCES} ${LIB_INCLUDES})
target_include_directories(${PROJECT_NAME} PUBLIC ${LIB_INCLUDE_DIRS})
