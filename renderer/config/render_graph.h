#pragma once

//#define RG_G_FRAMEBUFFER "framebuffer"
//#define RG_G_DS_VIEW "ds_view"

//#define RG_G_G_BUFFERS 

namespace PULSAR
{
	const char *const RG_G_FRAMEBUFFER = "framebuffer";
	const char *const RG_G_DS_VIEW = "ds_view";
	const char *const RG_G_VIEWPORT = "viewport";

	enum G_BUFFER
	{
		G_BUFFER_POS,
		G_BUFFER_ALBEDO,
		G_BUFFER_NORMAL,
		G_BUFFER_RMAE,		//	roughness, metalness, ambient, exposure
		G_BUFFERS_COUNT,
	};

	const char *const RG_G_G_BUFFERS[G_BUFFERS_COUNT] = { "g_buffer_pos", "g_buffer_albedo", "g_buffer_normal", "g_buffer_rmae" };
}
