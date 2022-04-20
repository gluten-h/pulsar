
cmake_minimum_required(VERSION 3.20)

project(pulsar LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_SUPPRESS_REGENERATION true)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_VS_SDK_INCLUDE_DIRECTORIES "$(IncludePath)" "$(DXSDK_DIR)Include")
set(CMAKE_VS_SDK_LIBRARY_DIRECTORIES "$(LibraryPath)" "$(DXSDK_DIR)Lib/x64")


set(CMAKE_LISTS "CMakeLists.txt" "lib/CMakeLists.txt" "renderer/CMakeLists.txt" "shaders/CMakeLists.txt")


add_executable(${PROJECT_NAME} WIN32 win_main.cpp)
target_sources(${PROJECT_NAME} PUBLIC ${CMAKE_LISTS})

set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "/MP /Ot /fp:fast /JMC")

add_subdirectory(lib)
add_subdirectory(renderer)
add_subdirectory(shaders)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})


find_program(NUGET_EXE NAMES nuget)
if (NOT NUGET_EXE)
	message(WARNING "Cannot find NuGet command line tool.\nInstall it with 'choco install nuget.commandline' or built-in VS-NuGet.")
else()
	exec_program(${NUGET_EXE} ARGS install "directxtex_desktop_2017" -Version 2021.8.2.1 -ExcludeVersion -OutputDirectory ${CMAKE_BINARY_DIR}/packages)
	exec_program(${NUGET_EXE} ARGS install "directxtk_desktop_2017" -Version 2021.8.2.1 -ExcludeVersion -OutputDirectory ${CMAKE_BINARY_DIR}/packages)

	target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR}/packages/directxtex_desktop_2017/build/native/directxtex_desktop_2017.targets)
	target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR}/packages/directxtk_desktop_2017/build/native/directxtk_desktop_2017.targets)
endif()


list(TRANSFORM LIB_SOURCES PREPEND "lib/")
list(TRANSFORM LIB_INCLUDES PREPEND "lib/")
list(TRANSFORM REN_SOURCES PREPEND "renderer/")
list(TRANSFORM REN_INCLUDES PREPEND "renderer/")
list(TRANSFORM SHADER_SOURCES PREPEND "shaders/")
list(TRANSFORM SHADER_INCLUDE_DIRS PREPEND "shaders/")

set_property(SOURCE ${SHADER_SOURCES} PROPERTY VS_SETTINGS "AdditionalIncludeDirectories=shaders/skybox/")
set_property(SOURCE ${SHADER_SOURCES} PROPERTY VS_SETTINGS "ExcludedFromBuild=true")

set(ALL_SOURCE_FILES win_main.cpp ${CMAKE_LISTS} ${LIB_SOURCES} ${LIB_INCLUDES} ${REN_SOURCES} ${REN_INCLUDES} ${SHADER_SOURCES})
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
