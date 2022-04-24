
cmake_minimum_required(VERSION 3.20)

set(LIB_SOURCES	
						core/bindables/cubemap/cubemap_data.cpp
						core/bindables/cubemap/cubemap_dds.cpp
						core/bindables/cubemap/cubemap.cpp
						core/bindables/depth_stencil/depth_stencil_state_data.cpp
						core/bindables/depth_stencil/depth_stencil_state.cpp
						core/bindables/depth_stencil/depth_stencil_view_data.cpp
						core/bindables/depth_stencil/depth_stencil_view.cpp
						core/bindables/dynamic_const_buffer/dynamic_const_buffer.cpp
						core/bindables/dynamic_const_buffer/dynamic_const_buffer_data.cpp
						core/bindables/dynamic_const_buffer/frag_dynamic_const_buffer.cpp
						core/bindables/dynamic_const_buffer/vert_dynamic_const_buffer.cpp
						core/bindables/input_layout/input_layout_data.cpp
						core/bindables/input_layout/input_layout.cpp
						core/bindables/mesh/mesh_d3d.cpp
						core/bindables/mesh/mesh_data.cpp
						core/bindables/mesh/mesh_obj.cpp
						core/bindables/mesh/mesh.cpp
						core/bindables/rasterizer_state/rasterizer_state_data.cpp
						core/bindables/rasterizer_state/rasterizer_state.cpp
						core/bindables/framebuffer/framebuffer_data.cpp
						core/bindables/framebuffer/framebuffer.cpp
						core/bindables/render_texture/render_texture_data.cpp
						core/bindables/render_texture/render_texture.cpp
						core/bindables/sampler/sampler_data.cpp
						core/bindables/sampler/sampler.cpp
						core/bindables/shaders/frag_shader_data.cpp
						core/bindables/shaders/frag_shader.cpp
						core/bindables/shaders/geom_shader_data.cpp
						core/bindables/shaders/geom_shader.cpp
						core/bindables/shaders/shader_data.cpp
						core/bindables/shaders/vert_shader_data.cpp
						core/bindables/shaders/vert_shader.cpp
						core/bindables/shader_texture/shader_texture_data.cpp
						core/bindables/shader_texture/shader_texture.cpp
						core/bindables/viewport/viewport_data.cpp
						core/bindables/viewport/viewport.cpp

						core/component/camera/camera/camera_data.cpp
						core/component/camera/camera/camera_def.cpp
						core/component/camera/camera/camera_get.cpp
						core/component/camera/camera/camera_update.cpp
						core/component/camera/camera/camera.cpp
						core/component/material/material/material_props.cpp
						core/component/skybox_material/skybox_material/skybox_material.cpp

						#core/d3d/id3d/pulsar_id3d.cpp
						#core/id3d/pulsar_d3d.cpp

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

						core/misc/shader_include/shader_include.cpp
						core/misc/skybox/skybox_data.cpp
						core/misc/skybox/skybox_def.cpp
						core/misc/skybox/skybox.cpp
						core/misc/texture2d/texture2d_data.cpp
						core/misc/texture2d/texture2d.cpp
						core/misc/transform/transform/transform.cpp

						core/node/node.cpp

						core/resource_manager/pulsar_resource_manager.cpp

						core/scene/scene_draw.cpp
						core/scene/scene_entity.cpp
						core/scene/scene_light.cpp
						core/scene/scene_skybox.cpp
						core/scene/scene_node.cpp


						ecs/types.cpp


						exceptions/base_exception/base_exception.cpp
						exceptions/gfx_exception/gfx_exception.cpp
						exceptions/rg_exception/rg_exception.cpp
						exceptions/win_exception/win_exception.cpp


						utils/pulsar_math.cpp
						utils/pulsar_utils.cpp


						window/window_cursor.cpp
						window/window_draw.cpp
						window/window_misc.cpp
						window/window_update.cpp
						window/window.cpp
						window/window_proc.cpp)
set(LIB_SOURCES ${LIB_SOURCES} PARENT_SCOPE)


set(LIB_INCLUDES		
						components/transform_component.h
						components/mesh_component.h


						containers/manager.h
						containers/fixed_vector.h
						containers/sparse_set.h


						core/bindables/bindable/bindable.h
						core/bindables/bindable/buffer_resource.h
						core/bindables/const_buffer/const_buffer.h
						core/bindables/const_buffer/frag_const_buffer.h
						core/bindables/const_buffer/vert_const_buffer.h
						core/bindables/cubemap/cubemap.h
						core/bindables/depth_stencil/depth_stencil_state.h
						core/bindables/depth_stencil/depth_stencil_view.h
						core/bindables/dynamic_const_buffer/dynamic_const_buffer.h
						core/bindables/dynamic_const_buffer/frag_dynamic_const_buffer.h
						core/bindables/dynamic_const_buffer/vert_dynamic_const_buffer.h
						core/bindables/input_layout/input_layout.h
						core/bindables/mesh/mesh.h
						core/bindables/rasterizer_state/rasterizer_state.h
						core/bindables/framebuffer/framebuffer.h
						core/bindables/render_texture/render_texture.h
						core/bindables/sampler/sampler.h
						core/bindables/shaders/frag_shader.h
						core/bindables/shaders/geom_shader.h
						core/bindables/shaders/shader.h
						core/bindables/shaders/vert_shader.h
						core/bindables/shader_texture/shader_texture.h
						core/bindables/viewport/viewport.h
						core/bindables/bindables.h

						core/component/camera/camera/camera.h
						core/component/camera/camera_shader/camera_deferred_shader.h
						core/component/camera/camera_shader/camera_post_effects_shader.h
						core/component/component/component.h
						core/component/material/material/material.h
						core/component/material/material_def.h
						core/component/skybox_material/skybox_material/skybox_material.h
						core/component/skybox_material/skybox_material_def.h
						core/component/skybox_material/skybox_material_shader.h
						core/component/components.h

						#core/d3d/id3d/pulsar_id3d.h
						core/id3d/pulsar_id3d.h
						#core/id3d/pulsar_d3d.h

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

						core/misc/shader_include/shader_include.h
						core/misc/skybox/skybox.h
						core/misc/texture2d/texture2d.h
						core/misc/transform/transform/transform.h
						core/misc/transform/transform_shader.h

						core/node/node.h

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

						core/scene/scene.h

						core/unclassified/unclassified.h


						dcb/dcb.h
						dcb/types.h
						dcb/layout_elem.h
						dcb/layout.h
						dcb/raw_layout.h
						dcb/baked_layout.h
						dcb/layout_elem_ref.h
						dcb/buffer.h


						def/def_cubemaps.h
						def/def_deferred.h
						def/def_materials.h
						def/def_meshes.h
						def/def_misc.h
						def/def_rasterizer_states.h
						def/def_system.h
						def/def_scene.h
						def/def_shaders.h
						def/def_skybox_materials.h
						def/def_skybox.h
						def/def_textures.h
						def/def_window.h
						def/pulsar_def.h


						ecs/types.h
						ecs/registry.h
						ecs/entity_bin_tree_array.h
						ecs/system.h


						exceptions/base_exception/base_exception.h
						exceptions/gfx_exception/gfx_exception.h
						exceptions/macro/def_exc_macros.h
						exceptions/macro/gfx_exc_macros.h
						exceptions/macro/rg_exc_macros.h
						exceptions/macro/win_exc_macros.h
						exceptions/rg_exception/rg_exception.h
						exceptions/win_exception/win_exception.h
						exceptions/pulsar_exc.h


						utils/pulsar_math.h
						utils/pulsar_utils.h
						utils/singleton.h


						window/window.h


						pulsar.h)
set(LIB_INCLUDES ${LIB_INCLUDES} PARENT_SCOPE)


set(LIB_INCLUDE_DIRS	
						containers


						core/bindables

						core/component/camera/camera
						core/component/camera/camera_shader
						core/component/component
						core/component/material/material
						core/component/material
						core/component/skybox_material/skybox_material
						core/component/skybox_material
						core/component

						#core/d3d/id3d
						core/id3d

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

						core/misc/shader_include
						core/misc/skybox
						core/misc/texture2d
						core/misc/transform/transform
						core/misc/transform

						core/resource_manager

						core/render_queue

						core/rg_component/render_graph
						core/rg_component/rg_component
						core/rg_component/rg_input
						core/rg_component/rg_pass
						core/rg_component/rg_source
						core/rg_component

						core/scene

						core/unclassified


						core


						def


						exceptions/base_exception
						exceptions/gfx_exception
						exceptions/macros
						exceptions/rg_exception
						exceptions/win_exception


						#utils


						window


						./)

target_sources(${PROJECT_NAME} PUBLIC ${LIB_SOURCES} ${LIB_INCLUDES})
target_include_directories(${PROJECT_NAME} PUBLIC ${LIB_INCLUDE_DIRS})
