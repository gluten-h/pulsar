
cmake_minimum_required(VERSION 3.20)

set(SHADER_SOURCES			deferred/light/dir_light.hlsli
							deferred/light/point_light.hlsli
							deferred/deferred_fs.hlsl

							g_buffer/g_buffer_pass_fs.hlsl
							g_buffer/g_buffer_pass_gs.hlsl
							g_buffer/g_buffer_pass_vs.hlsl
							
							misc/brdf/cook_torrance.hlsli
							misc/brdf/oren_nayar.hlsli
							misc/normal_mapping.hlsli

							post_effects/gamma_correction.hlsli
							post_effects/post_effects_fs.hlsl
							post_effects/tone_mapping.hlsli

							skybox/skybox_fs.hlsl
							skybox/skybox_vs.hlsl

							utils/fullscreen_vs.hlsl)
set(SHADER_SOURCES ${SHADER_SOURCES} PARENT_SCOPE)

SET(SHADER_INCLUDE_DIRS		deferred/light
							deferred

							g_buffer

							misc/brdf
							misc

							post_effects

							utils

							.)
set(SHADER_INCLUDE_DIRS ${SHADER_INCLUDE_DIRS} PARENT_SCOPE)


target_sources(${PROJECT_NAME} PUBLIC ${SHADER_SOURCES})
