cmake_minimum_required(VERSION 3.20)

project(pulsar LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_SUPPRESS_REGENERATION true)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

set(ADDITIONAL_FILES "TODO.md" "CMakeLists.txt" "lib/CMakeLists.txt" "renderer/CMakeLists.txt" "shaders/CMakeLists.txt")

add_executable(${PROJECT_NAME} WIN32 win_main.cpp)
target_sources(${PROJECT_NAME} PUBLIC ${ADDITIONAL_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "/MP /Ot /JMC")

add_subdirectory(lib)
add_subdirectory(renderer)
add_subdirectory(shaders)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

include(${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake)
find_package(directxmath REQUIRED)
find_package(directxtex CONFIG REQUIRED)
find_package(directxtk CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE d3d11 dxgi dxguid d3dcompiler uuid
												Microsoft::DirectXTex Microsoft::DirectXTK)

list(TRANSFORM LIB_SOURCES PREPEND "lib/")
list(TRANSFORM LIB_INCLUDES PREPEND "lib/")
list(TRANSFORM REN_SOURCES PREPEND "renderer/")
list(TRANSFORM REN_INCLUDES PREPEND "renderer/")
list(TRANSFORM SHADER_SOURCES PREPEND "shaders/")
list(TRANSFORM SHADER_INCLUDE_DIRS PREPEND "shaders/")

set_property(SOURCE ${SHADER_SOURCES} PROPERTY VS_SETTINGS "ExcludedFromBuild=true")

set(ALL_SOURCE_FILES ${ADDITIONAL_FILES} ${LIB_SOURCES} ${LIB_INCLUDES} ${REN_SOURCES} ${REN_INCLUDES} ${SHADER_SOURCES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${ALL_SOURCE_FILES})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)


set(SHADER_INCLUDE_DIRS_DELIM "?")
set(SHADER_INCLUDE_MACRO_STR "")
foreach(_shader_inc IN LISTS SHADER_INCLUDE_DIRS)
	get_filename_component(_abs_path ${_shader_inc} ABSOLUTE)
	string(APPEND SHADER_INCLUDE_MACRO_STR ${_abs_path} "${SHADER_INCLUDE_DIRS_DELIM}")
endforeach()


function(add_project_macros target) 
	get_target_property(_src ${target} SOURCES)

	foreach (FILE_PATH IN LISTS _src)
		set_property(SOURCE ${FILE_PATH} APPEND PROPERTY COMPILE_DEFINITIONS PULSAR_ROOT_PATH=L"${CMAKE_SOURCE_DIR}")
		set_property(SOURCE ${FILE_PATH} APPEND PROPERTY COMPILE_DEFINITIONS PULSAR_SHADER_INCLUDE_DIRS=L"${SHADER_INCLUDE_MACRO_STR}")
	endforeach()
endfunction()

add_project_macros(${PROJECT_NAME})
