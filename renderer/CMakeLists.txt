
cmake_minimum_required(VERSION 3.20)

set(REN_SOURCES			
						components/camera/camera.cpp
						components/camera/perspective_camera.cpp

						components/material/material.cpp
						components/material/material_props.cpp

						components/mesh/mesh_d3d.cpp
						components/mesh/mesh_data.cpp
						components/mesh/mesh_obj.cpp
						components/mesh/mesh.cpp

						deferred_buffer/deferred_buffer_get.cpp

						misc/cam_controller/cam_controller.cpp

						node/node.cpp

						scene/scene.cpp
						scene/scene_draw.cpp
						scene/scene_light.cpp
						scene/scene_skybox.cpp
						scene/scene_node.cpp

						pulsar_render_graph/pulsar_render_graph.cpp

						passes/clear_buffers_pass.cpp
						passes/present_pass.cpp
						passes/g_buffer_pass.cpp)
set(REN_SOURCES ${REN_SOURCES} PARENT_SCOPE)

set(REN_INCLUDES		
						components/camera/camera.h
						components/camera/perspective_camera.h
						components/camera/camera_component.h

						components/transform/transform_component.h

						components/material/material.h
						components/material/material_component.h

						components/mesh/mesh.h
						components/mesh/mesh_component.h

						components/components.h

						config/camera.h
						config/cubemap.h
						config/deferred.h
						config/material.h
						config/mesh.h
						config/misc.h
						config/rasterizer_state.h
						config/render_graph.h
						config/scene.h
						config/shader.h
						config/skybox_material.h
						config/skybox.h
						config/shader_texture.h
						config/window.h
						config/pulsar.h

						deferred_buffer/deferred_buffer.h

						managers/win_manager.h
						managers/bindable_manager.h
						managers/component_manager.h
						managers/entity_manager.h
						managers/light_manager.h
						managers/rg_component_manager.h
						managers/scene_manager.h

						misc/cam_controller/cam_controller.h

						node/node.h

						scene/scene.h

						pulsar_render_graph/pulsar_render_graph.h

						passes/fullscreen_pass.h
						passes/render_queue_pass.h
						passes/clear_buffers_pass.h
						passes/present_pass.h
						passes/g_buffer_pass.h)
set(REN_INCLUDES ${REN_INCLUDES} PARENT_SCOPE)

set(REN_INCLUDE_DIRS	

						components

						deferred_buffer

						managers/win_manager
						managers

						misc/cam_controller
						./)

target_sources(${PROJECT_NAME} PUBLIC ${REN_SOURCES} ${REN_INCLUDES})
target_include_directories(${PROJECT_NAME} PUBLIC ${REN_INCLUDE_DIRS})
