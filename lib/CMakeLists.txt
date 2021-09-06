
cmake_minimum_required(VERSION 3.20)

set(LIB_SOURCES 		core/bindable/bindable/bindable.cpp
						core/bindable/cubemap/cubemap_data.cpp
						core/bindable/cubemap/cubemap_dds.cpp
						core/bindable/cubemap/cubemap.cpp
						core/bindable/depth_stencil/state/depth_stencil_state_data.cpp
						core/bindable/depth_stencil/state/depth_stencil_state.cpp
						core/bindable/depth_stencil/view/depth_stencil_view_data.cpp
						core/bindable/depth_stencil/view/depth_stencil_view_get.cpp
						core/bindable/depth_stencil/view/depth_stencil_view.cpp
						core/bindable/input_layout/input_layout_data.cpp
						core/bindable/input_layout/input_layout.cpp
						core/bindable/mesh/mesh_d3d.cpp
						core/bindable/mesh/mesh_data.cpp
						core/bindable/mesh/mesh_obj.cpp
						core/bindable/mesh/mesh.cpp
						core/bindable/rasterizer_state/rasterizer_state_data.cpp
						core/bindable/rasterizer_state/rasterizer_state.cpp
						core/bindable/render_target/render_target_data.cpp
						core/bindable/render_target/render_target_misc.cpp
						core/bindable/render_target/render_target.cpp
						core/bindable/render_texture/render_texture_data.cpp
						core/bindable/render_texture/render_texture_get.cpp
						core/bindable/render_texture/render_texture_misc.cpp
						core/bindable/render_texture/render_texture.cpp
						core/bindable/sampler/sampler_data.cpp
						core/bindable/sampler/sampler.cpp
						core/bindable/shader/frag/frag_shader_data.cpp
						core/bindable/shader/frag/frag_shader.cpp
						core/bindable/shader/geom/geom_shader_data.cpp
						core/bindable/shader/geom/geom_shader.cpp
						core/bindable/shader/shader/shader_data.cpp
						core/bindable/shader/vert/vert_shader_data.cpp
						core/bindable/shader/vert/vert_shader.cpp
						core/bindable/texture/texture_data.cpp
						core/bindable/texture/texture.cpp
						core/bindable/viewport/viewport_data.cpp
						core/bindable/viewport/viewport.cpp

						core/component/camera/camera/camera_data.cpp
						core/component/camera/camera/camera_def.cpp
						core/component/camera/camera/camera_get.cpp
						core/component/camera/camera/camera_update.cpp
						core/component/camera/camera/camera.cpp
						core/component/material/material/material.cpp
						core/component/skybox_material/skybox_material/skybox_material.cpp

						core/d3d/id3d/pulsar_id3d.cpp
						core/d3d/pulsar_d3d.cpp

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

						core/resource_manager/pulsar_resource_manager.cpp

						core/scene/scene_draw.cpp
						core/scene/scene_entity.cpp
						core/scene/scene_light.cpp
						core/scene/scene_skybox.cpp


						exception/exception/exception.cpp
						exception/gfx_exception/gfx_exception.cpp
						exception/rg_exception/rg_exception.cpp
						exception/win_exception/win_exception.cpp


						utils/pulsar_math.cpp
						utils/pulsar_utils.cpp


						window/window_cursor.cpp
						window/window_draw.cpp
						window/window_misc.cpp
						window/window_update.cpp
						window/window.cpp)
set(LIB_SOURCES ${LIB_SOURCES} PARENT_SCOPE)


set(LIB_INCLUDES		containers/manager/manager.h
						containers/piston/piston.h


						core/bindable/bindable/bindable.h
						core/bindable/bindable/buffer_resource.h
						core/bindable/const_buffer/const_buffer.h
						core/bindable/const_buffer/const_buffers.h
						core/bindable/const_buffer/frag_const_buffer.h
						core/bindable/const_buffer/vert_const_buffer.h
						core/bindable/cubemap/cubemap.h
						core/bindable/depth_stencil/state/depth_stencil_state.h
						core/bindable/depth_stencil/view/depth_stencil_view.h
						core/bindable/depth_stencil/depth_stencil.h
						core/bindable/input_layout/input_layout.h
						core/bindable/mesh/mesh.h
						core/bindable/rasterizer_state/rasterizer_state.h
						core/bindable/render_target/render_target.h
						core/bindable/render_texture/render_texture.h
						core/bindable/sampler/sampler.h
						core/bindable/shader/frag/frag_shader.h
						core/bindable/shader/geom/geom_shader.h
						core/bindable/shader/shader/shader.h
						core/bindable/shader/vert/vert_shader.h
						core/bindable/shader/shaders.h
						core/bindable/texture/texture.h
						core/bindable/viewport/viewport.h
						core/bindable/bindables.h

						core/component/camera/camera/camera.h
						core/component/camera/camera_shader/camera_deferred_shader.h
						core/component/camera/camera_shader/camera_post_effects_shader.h
						core/component/component/component.h
						core/component/material/material/material.h
						core/component/material/material_def.h
						core/component/material/material_shader.h
						core/component/skybox_material/skybox_material/skybox_material.h
						core/component/skybox_material/skybox_material_def.h
						core/component/skybox_material/skybox_material_shader.h
						core/component/components.h

						core/d3d/id3d/pulsar_id3d.h
						core/d3d/pulsar_d3d.h

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

						core/resource_manager/pulsar_resource_manager.h

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


						exception/exception/exception.h
						exception/gfx_exception/gfx_exception.h
						exception/macros/def_exc_macros.h
						exception/macros/exc_macros.h
						exception/macros/gfx_exc_macros.h
						exception/macros/rg_exc_macros.h
						exception/macros/win_exc_macros.h
						exception/rg_exception/rg_exception.h
						exception/win_exception/win_exception.h


						utils/pulsar_math.h
						utils/pulsar_utils.h


						window/window.h


						pulsar.h)
set(LIB_INCLUDES ${LIB_INCLUDES} PARENT_SCOPE)


set(LIB_INCLUDE_DIRS	containers/manager
						containers/piston


						core/bindable/bindable
						core/bindable/const_buffer
						core/bindable/cubemap
						core/bindable/depth_stencil/state
						core/bindable/depth_stencil/view
						core/bindable/depth_stencil
						core/bindable/input_layout
						core/bindable/mesh
						core/bindable/rasterizer_state
						core/bindable/render_target
						core/bindable/render_texture
						core/bindable/sampler
						core/bindable/shader/frag
						core/bindable/shader/geom
						core/bindable/shader/shader
						core/bindable/shader/vert
						core/bindable/shader
						core/bindable/texture
						core/bindable/viewport
						core/bindable

						core/component/camera/camera
						core/component/camera/camera_shader
						core/component/component
						core/component/material/material
						core/component/material
						core/component/skybox_material/skybox_material
						core/component/skybox_material
						core/component

						core/d3d/id3d
						core/d3d

						core/entity/entity
						core/entity/light/dir
						core/entity/light/light
						core/entity/light/point
						core/entity/light
						core/entity/object
						core/entity

						core/filesystem

						core/gfx

						core/input/mouse
						core/input

						core/misc/shader_include
						core/misc/skybox
						core/misc/texture2d
						core/misc/transform/transform
						core/misc/transform

						core/resource_manager

						core/rg_component/render_graph
						core/rg_component/rg_component
						core/rg_component/rg_input
						core/rg_component/rg_pass
						core/rg_component/rg_source
						core/rg_component

						core/scene


						def


						exception/exception
						exception/gfx_exception
						exception/macros
						exception/rg_exception
						exception/win_exception


						utils


						window


						./)



target_sources(${PROJECT_NAME} PUBLIC ${LIB_SOURCES} ${LIB_INCLUDES})
target_include_directories(${PROJECT_NAME} PUBLIC ${LIB_INCLUDE_DIRS})
