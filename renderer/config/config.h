#pragma once

#include <stdint.h>
#include <esent.h>
#include <tchar.h>
#include <Windows.h>
#include "utils/math.h"
#include <dxgiformat.h>


namespace pulsar
{
	// PATHS
	const WCHAR *const BLACK_CUBEMAP_PATH = L"resources/pulsar/cubemap_black.dds";
	const WCHAR *const WHITE_CUBEMAP_PATH = L"resources/pulsar/cubemap_white.dds";

	const WCHAR *const SPHERE16_OBJ_PATH = L"resources/pulsar/sphere16.obj";
	const WCHAR *const SPHERE32_OBJ_PATH = L"resources/pulsar/sphere32.obj";
	const WCHAR *const SPHERE64_OBJ_PATH = L"resources/pulsar/sphere64.obj";

	const WCHAR *const FULLSCREEN_VS_PATH = L"shaders/utils/fullscreen_vs.hlsl";
	const WCHAR *const G_BUFFER_VS_PATH = L"shaders/g_buffer/g_buffer_vs.hlsl";
	const WCHAR *const G_BUFFER_GS_PATH = L"shaders/g_buffer/g_buffer_gs.hlsl";
	const WCHAR *const OPAQUE_G_BUFFER_FS_PATH = L"shaders/g_buffer/g_buffer_fs.hlsl";
	const WCHAR *const DEFERRED_FS_PATH = L"shaders/deferred/deferred_fs.hlsl";
	const WCHAR *const SHADOW_PASS_VS_PATH = L"shaders/shadows/shadow_pass_vs.hlsl";
	const WCHAR *const SHADOW_PASS_FS_PATH = L"shaders/shadows/shadow_pass_fs.hlsl";

	const WCHAR *const SKYBOX_VS_PATH = L"shaders/skybox/skybox_vs.hlsl";
	const WCHAR *const SKYBOX_FS_PATH = L"shaders/skybox/skybox_fs.hlsl";

	const WCHAR *const POST_EFFECTS_FS_PATH = L"shaders/post_effects/post_effects_fs.hlsl";

	const WCHAR *const WHITE_QUAD_PATH = L"resources/pulsar/quad_white.png";
	const WCHAR *const BLACK_QUAD_PATH = L"resources/pulsar/quad_black.png";
	const WCHAR *const NORMAL_QUAD_PATH = L"resources/pulsar/quad_normal.png";

	// CONSTANTS
	const WCHAR SHADER_INCLUDE_DIRS_DELIM = L'?';

	const uint16_t MAX_VIEWPORT_RQ_JOBS = 1024u;
	enum VIEWPORT_RQ_MODE
	{
		VIEWPORT_RQ_OPAQUE,
		VIEWPORT_RQ_MODES_COUNT
	};

	const uint16_t MAX_SHADOWS_RQ_JOBS = 1024u;
	enum SHADOWS_RQ_MODE
	{
		SHADOWS_RQ_OPAQUE,
		SHADOWS_RQ_MODES_COUNT
	};

	const XMUINT2 SHADOW_ATLAS_SIZE = { 6144u, 6144u };
	const DXGI_FORMAT SHADOW_ATLAS_FORMAT = DXGI_FORMAT_R32_FLOAT;

	const uint8_t SHADOW_FILTER_SIZE = 32u;
	const uint8_t SHADOW_FILTER_SAMPLES = 8u;

	const char *const RG_G_FRAMEBUFFER = "framebuffer";
	const char *const RG_G_DSV = "dsv";
	const char *const RG_G_HDR_BUFFER = "hdr_buffer";

	enum G_BUFFER
	{
		G_BUFFER_POS,
		G_BUFFER_ALBEDO,
		G_BUFFER_SURFACE_NORMAL,
		G_BUFFER_NORMAL,
		G_BUFFER_RMAE,				//roughness, metalness, ambient, exposure
		G_BUFFER_IRRADIANCE,
		G_BUFFERS_COUNT,
	};
	const char *const RG_G_G_BUFFERS[G_BUFFERS_COUNT] = { "g_buffer_pos", "g_buffer_albedo", "g_buffer_surface_normal", "g_buffer_normal", "g_buffer_rmae", "g_buffer_irradiance" };
	const char *const RG_G_VIEWPORT_RQ = "viewport_rq";
	const char *const RG_G_SHADOWS_RQ = "shadows_rq";

	enum RG_PASS_LEVEL
	{
		RG_CLEAR_BUFFERS_PASS_LEVEL = 0u,
		RG_SHADOW_MAPPING_PASS_LEVEL = 1u,
		RG_G_BUFFER_PASS_LEVEL = 2u,
		RG_DEFERRED_PASS_LEVEL = 3u,
		RG_SKYBOX_PASS_LEVEL = 4u,
		RG_POST_EFFECTS_PASS_LEVEL = 5u,
		RG_PRESENT_PASS_LEVEL = 6u
	};
	const char *const RG_CLEAR_BUFFERS_PASS_NAME = "clear_buffers";
	const char *const RG_SHADOW_MAPPING_PASS_NAME = "shadow_mapping";
	const char *const RG_G_BUFFER_PASS_NAME = "g_buffer";
	const char *const RG_DEFERRED_PASS_NAME = "deferred";
	const char *const RG_SKYBOX_PASS_NAME = "skybox";
	const char *const RG_POST_EFFECTS_PASS_NAME = "post_effects";
	const char *const RG_PRESENT_PASS_NAME = "present";

	const uint16_t MAX_SCENE_LIGHTS_COUNT = 256u;

	const uint8_t DELTA_TIME_FRAMES_SKIP_COUNT = 8u;
	const struct
	{
		const LPCTSTR class_name = __T("pulsar");
		const LPCSTR name = "pulsar";
		const DWORD style = WS_VISIBLE | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU;
		UINT width = 1280;
		UINT height = 720;
	} DEFAULT_WINDOW_SETTINGS;

	const char *const DEFAULT_ENTITY_NAME = "entity";

	const uint32_t DEFAULT_ENTITY_VIEWPORT_MASK = 0x01;
	const uint32_t DEFAULT_ENTITY_SHADOWS_MASK = 0xFFFFFFFF;
	const uint32_t DEFAULT_CAMERA_VIEWPORT_MASK = 0xFFFFFFFF;

	// SLOTS
	const uint8_t FRAG_G_BUFFER_MATERIAL_SLOT = 0u;
	const uint8_t FRAG_G_BUFFER_MATERIAL_ALBEDO_MAP_SLOT = 0u;
	const uint8_t FRAG_G_BUFFER_MATERIAL_NORMAL_MAP_SLOT = 1u;
	const uint8_t FRAG_G_BUFFER_MATERIAL_ROUGHNESS_MAP_SLOT = 2u;
	const uint8_t FRAG_G_BUFFER_MATERIAL_METALNESS_MAP_SLOT = 3u;
	const uint8_t FRAG_G_BUFFER_MATERIAL_AO_MAP_SLOT = 4u;
	const uint8_t FRAG_G_BUFFER_MATERIAL_EXPOSURE_MAP_SLOT = 5u;
	const uint8_t FRAG_G_BUFFER_MATERIAL_IRRADIANCE_MAP_SLOT = 6u;

	const uint8_t FRAG_SKYBOX_SKYBOX_MATERIAL_ALBEDO_MAP_SLOT = 0u;
	const uint8_t FRAG_SKYBOX_SKYBOX_MATERIAL_EXPOSURE_MAP_SLOT = 1u;

	const uint8_t VERT_TRANSFORM_SLOT = 0u;
	const uint8_t VERT_SHADOW_TRANSFORM_VIEW_SLOT = 1u;
	const uint8_t VERT_SHADOW_TRANSFORM_PROJ_SLOT = 2u;
	const uint8_t FRAG_SHADOW_LIGHT_TRANSFORM_SLOT = 0u;
	const uint8_t VERT_G_BUFFER_CAMERA_SLOT = 1u;
	const uint8_t FRAG_DEFERRED_LIGHTS_SLOT = 0u;
	const uint8_t FRAG_DEFERRED_CAMERA_SLOT = 1u;
	const uint8_t FRAG_DEFERRED_SHADOW_ATLAS_SLOT = 6u;
	const uint8_t FRAG_DEFERRED_SHADOW_FILTER_SLOT = 7u;
	const uint8_t VERT_SKYBOX_CAMERA_SLOT = 0u;
	const uint8_t FRAG_SKYBOX_SKYBOX_MATERIAL_SLOT = 0u;
	const uint8_t FRAG_SKYBOX_CAMERA_SLOT = 1u;
	const uint8_t FRAG_POST_EFFECTS_HDR_BUFFER_SLOT = 0u;
	const uint8_t FRAG_POST_EFFECTS_CAMERA_SLOT = 0u;

	const uint8_t FRAG_G_BUFFER_SAMPLER_SLOT = 0u;
	const uint8_t FRAG_DEFERRED_SAMPLER_SLOT = 0u;
	const uint8_t FRAG_DEFERRED_SHADOW_SAMPLER_SLOT = 1u;
	const uint8_t FRAG_SKYBOX_SAMPLER_SLOT = 0u;
	const uint8_t FRAG_POST_EFFECTS_SAMPLER_SLOT = 0u;

	// DCB
	const char *const MATERIAL_DCB_ALBEDO_COLOR = "c";
	const char *const MATERIAL_DCB_ALBEDO_MAP_SRGB = "s";
	const char *const MATERIAL_DCB_NORMAL_FACTOR = "n";
	const char *const MATERIAL_DCB_ROUGHNESS = "r";
	const char *const MATERIAL_DCB_METALNESS = "m";
	const char *const MATERIAL_DCB_AO = "a";
	const char *const MATERIAL_DCB_EXPOSURE = "e";
	const char *const MATERIAL_DCB_IRRADIANCE_COLOR = "i";

	const char *const SKYBOX_MATERIAL_DCB_ALBEDO_COLOR = "c";
	const char *const SKYBOX_MATERIAL_DCB_ALBEDO_SRGB = "s";
	const char *const SKYBOX_MATERIAL_DCB_EXPOSURE = "e";
}
