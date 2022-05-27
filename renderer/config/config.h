#pragma once

#include <cstdint>
#include <esent.h>
#include <tchar.h>
#include <Windows.h>


namespace pulsar
{
	// PATHS
	const WCHAR *const BLACK_CUBEMAP_PATH = L"resources/pulsar/cubemap_black.dds";
	const WCHAR *const WHITE_CUBEMAP_PATH = L"resources/pulsar/cubemap_white.dds";

	const WCHAR *const CUBE_OBJ_PATH = L"resources/pulsar/cube.obj";
	const WCHAR *const SPHERE16_OBJ_PATH = L"resources/pulsar/sphere16.obj";
	const WCHAR *const SPHERE32_OBJ_PATH = L"resources/pulsar/sphere32.obj";
	const WCHAR *const SPHERE64_OBJ_PATH = L"resources/pulsar/sphere64.obj";

	const WCHAR *const FULLSCREEN_VS_PATH = L"shaders/utils/fullscreen_vs.hlsl";
	const WCHAR *const G_BUFFER_VS_PATH = L"shaders/g_buffer/g_buffer_vs.hlsl";
	const WCHAR *const G_BUFFER_GS_PATH = L"shaders/g_buffer/g_buffer_gs.hlsl";
	const WCHAR *const OPAQUE_G_BUFFER_FS_PATH = L"shaders/g_buffer/g_buffer_fs.hlsl";
	const WCHAR *const DEFERRED_FS_PATH = L"shaders/deferred/deferred_fs.hlsl";

	const WCHAR *const SKYBOX_VS_PATH = L"shaders/skybox/skybox_vs.hlsl";
	const WCHAR *const SKYBOX_FS_PATH = L"shaders/skybox/skybox_fs.hlsl";

	const WCHAR *const POST_EFFECTS_FS_PATH = L"shaders/post_effects/post_effects_fs.hlsl";

	const WCHAR *const WHITE_QUAD_PATH = L"resources/pulsar/quad_white.png";
	const WCHAR *const BLACK_QUAD_PATH = L"resources/pulsar/quad_black.png";
	const WCHAR *const NORMAL_QUAD_PATH = L"resources/pulsar/quad_normal.png";

	// CONSTANTS
	const WCHAR SHADER_INCLUDE_DIRS_DELIM = L'?';

	const char *const RG_G_FRAMEBUFFER = "framebuffer";
	const char *const RG_G_DS_VIEW = "ds_view";
	const char *const RG_G_VIEWPORT = "viewport";
	const char *const RG_G_HDR_BUFFER = "hdr_buffer";

	enum G_BUFFER
	{
		G_BUFFER_POS,
		G_BUFFER_ALBEDO,
		G_BUFFER_NORMAL,
		G_BUFFER_RMAE,		//	roughness, metalness, ambient, exposure
		G_BUFFERS_COUNT,
	};
	const char *const RG_G_G_BUFFERS[G_BUFFERS_COUNT] = { "g_buffer_pos", "g_buffer_albedo", "g_buffer_normal", "g_buffer_rmae" };

	const uint16_t MAX_SCENE_LIGHTS_COUNT = 1024u;

	const uint8_t FPS_FRAMES_SKIP_COUNT = 8u;
	const struct
	{
		const LPCTSTR class_name = __T("pulsar");
		const LPCSTR name = "pulsar";
		const DWORD style = WS_VISIBLE | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU;
		int width = 1280;
		int height = 720;
	} DEFAULT_WINDOW_SETTINGS;


	// SLOTS
	const uint8_t G_BUFFER_FRAG_MATERIAL_ALBEDO_MAP_SLOT = 0u;
	const uint8_t G_BUFFER_FRAG_MATERIAL_NORMAL_MAP_SLOT = 1u;
	const uint8_t G_BUFFER_FRAG_MATERIAL_ROUGHNESS_MAP_SLOT = 2u;
	const uint8_t G_BUFFER_FRAG_MATERIAL_METALNESS_MAP_SLOT = 3u;
	const uint8_t G_BUFFER_FRAG_MATERIAL_AO_MAP_SLOT = 4u;
	const uint8_t G_BUFFER_FRAG_MATERIAL_EXPOSURE_MAP_SLOT = 5u;

	const uint8_t SKYBOX_FRAG_SKYBOX_MATERIAL_ALBEDO_MAP_SLOT = 0u;
	const uint8_t SKYBOX_FRAG_SKYBOX_MATERIAL_EXPOSURE_MAP_SLOT = 1u;

	const uint8_t G_BUFFER_VERT_TRANSFORM_SLOT = 0u;
	const uint8_t G_BUFFER_FRAG_MATERIAL_SLOT = 0u;
	const uint8_t G_BUFFER_VERT_CAMERA_SLOT = 1u;
	const uint8_t DEFERRED_FRAG_LIGHTS_SLOT = 0u;
	const uint8_t DEFERRED_FRAG_CAMERA_SLOT = 1u;
	const uint8_t SKYBOX_VERT_CAMERA_SLOT = 0u;
	const uint8_t SKYBOX_FRAG_SKYBOX_MATERIAL_SLOT = 0u;
	const uint8_t SKYBOX_FRAG_CAMERA_SLOT = 1u;
	const uint8_t POST_EFFECTS_FRAG_HDR_BUFFER_SLOT = 0u;
	const uint8_t POST_EFFECTS_FRAG_CAMERA_SLOT = 0u;

	const uint8_t G_BUFFER_FRAG_SAMPLER_SLOT = 0u;
	const uint8_t DEFERRED_FRAG_SAMPLER_SLOT = 0u;
	const uint8_t SKYBOX_FRAG_SAMPLER_SLOT = 0u;
	const uint8_t POST_EFFECTS_FRAG_SAMPLER_SLOT = 0u;

	// DCB
	const char *const TRANSFORM_DCB_MODEL = "model";
	const char *const TRANSFORM_DCB_NORM = "norm";

	const char *const MATERIAL_DCB_ALBEDO_COLOR = "albedo_color";
	const char *const MATERIAL_DCB_ALBEDO_MAP_SRGB = "albedo_srgb";
	const char *const MATERIAL_DCB_NORMAL_FACTOR = "normal_factor";
	const char *const MATERIAL_DCB_ROUGHNESS = "roughness";
	const char *const MATERIAL_DCB_METALNESS = "metalness";
	const char *const MATERIAL_DCB_AO = "ao";
	const char *const MATERIAL_DCB_EXPOSURE = "exposure";

	const char *const SKYBOX_MATERIAL_DCB_ALBEDO_COLOR = "albedo_color";
	const char *const SKYBOX_MATERIAL_DCB_ALBEDO_SRGB = "albedo_srgb";
	const char *const SKYBOX_MATERIAL_DCB_EXPOSURE = "exposure";
}
