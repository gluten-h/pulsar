
cmake_minimum_required(VERSION 3.20)

set(REN_SOURCES			deferred_buffer/deferred_buffer_get.cpp

						managers/win_manager/win_manager.cpp
						managers/win_manager/wm_cursor.cpp
						managers/win_manager/wm_misc.cpp
						managers/win_manager/wm_resources.cpp
						managers/win_manager/wm_update.cpp
						managers/win_manager/wm_win_proc.cpp
						managers/win_manager/wm_window.cpp

						misc/cam_controller/cam_controller.cpp)
set(REN_SOURCES ${REN_SOURCES} PARENT_SCOPE)

set(REN_INCLUDES		deferred_buffer/deferred_buffer.h

						managers/win_manager/win_manager.h
						managers/bindable_manager.h
						managers/component_manager.h
						managers/entity_manager.h
						managers/light_manager.h
						managers/rg_component_manager.h
						managers/scene_manager.h

						misc/cam_controller/cam_controller.h

						render_graph/rg.h

						rg_lib/base_pass/rg_bindable_pass.h
						rg_lib/base_pass/rg_fullscreen_pass.h
						rg_lib/pass/buffer_clear_pass.h
						rg_lib/pass/present_pass.h)
set(REN_INCLUDES ${REN_INCLUDES} PARENT_SCOPE)

set(REN_INCLUDE_DIRS	deferred_buffer

						managers/win_manager
						managers

						misc/cam_controller

						render_graph

						rg_lib/base_pass
						rg_lib/pass
						
						./)



target_sources(${PROJECT_NAME} PUBLIC ${REN_SOURCES} ${REN_INCLUDES})
target_include_directories(${PROJECT_NAME} PUBLIC ${REN_INCLUDE_DIRS})
