
cmake_minimum_required(VERSION 3.20)

set(REN_SOURCES			
						components/camera/camera.cpp
						components/camera/perspective_camera.cpp

						components/transform/transform.cpp
						components/transform/transform_attr.cpp

						components/material/material.cpp
						components/material/material_props.cpp

						components/mesh/mesh_d3d.cpp
						components/mesh/mesh_data.cpp
						components/mesh/mesh_obj.cpp
						components/mesh/mesh.cpp

						components/light/light.cpp
						components/light/point_light.cpp
						components/light/dir_light.cpp

						components/skybox_material/skybox_material.cpp
						components/skybox_material/skybox_material_props.cpp

						misc/cam_controller/cam_controller.cpp

						node/node.cpp

						renderer/renderer.cpp

						scene/scene.cpp
						scene/scene_node.cpp

						scripts/camera_controller.cpp

						systems/camera_system.cpp
						systems/render_system.cpp
						systems/light_system.cpp
						systems/script_system.cpp

						pulsar_render_graph/deferred_render_graph.cpp

						passes/clear_buffers_pass.cpp
						passes/present_pass.cpp
						passes/g_buffer_pass.cpp
						passes/deferred_pass.cpp
						passes/skybox_pass.cpp
						passes/post_effects_pass.cpp)
set(REN_SOURCES ${REN_SOURCES} PARENT_SCOPE)

set(REN_INCLUDES		
						components/camera/camera.h
						components/camera/perspective_camera.h
						components/camera/camera_component.h

						components/transform/transform.h
						components/transform/transform_component.h

						components/material/material.h
						components/material/material_component.h

						components/mesh/mesh.h
						components/mesh/mesh_component.h

						components/light/light.h
						components/light/point_light.h
						components/light/dir_light.h
						components/light/light_component.h

						components/skybox_material/skybox_material.h

						components/script/script.h
						components/script/script_component.h

						components/components.h

						config/pulsar_config.h
						config/config.h
						config/cubemap.h
						config/material.h
						config/mesh.h
						config/rasterizer_state.h
						config/shader.h
						config/shader_texture.h

						misc/cam_controller/cam_controller.h

						node/node.h

						renderer/renderer.h

						scene/scene.h

						scripts/camera_controller.h

						systems/camera_system.h
						systems/render_system.h
						systems/light_system.h
						systems/script_system.h

						pulsar_render_graph/deferred_render_graph.h

						passes/fullscreen_pass.h
						passes/clear_buffers_pass.h
						passes/present_pass.h
						passes/g_buffer_pass.h
						passes/deferred_pass.h
						passes/skybox_pass.h
						passes/post_effects_pass.h

						pulsar.h)
set(REN_INCLUDES ${REN_INCLUDES} PARENT_SCOPE)

set(REN_INCLUDE_DIRS	

						components

						misc/cam_controller
						./)

target_sources(${PROJECT_NAME} PUBLIC ${REN_SOURCES} ${REN_INCLUDES})
target_include_directories(${PROJECT_NAME} PUBLIC ${REN_INCLUDE_DIRS})
