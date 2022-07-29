#pragma once

#include "gfx/gfx.h"


namespace pulsar
{
	const LPCSTR VERT_TARGET = "vs_5_0";
	const LPCSTR GEOM_TARGET = "gs_5_0";
	const LPCSTR FRAG_TARGET = "ps_5_0";

	const LPCSTR VERT_ENTRY = "vert";
	const LPCSTR GEOM_ENTRY = "geom";
	const LPCSTR FRAG_ENTRY = "frag";

	class shader
	{
	private:
		ID3DBlob *mp_blob = NULL;

	protected:
		shader &operator=(const shader&) = delete;
		shader &operator=(shader&&) = delete;
		shader(const shader&) = delete;
		shader(shader&&) = delete;
		shader() = default;
		virtual ~shader();

		void	create_shader_blob(const LPCWSTR shader_file, const LPCSTR entry, const LPCSTR target);
		void	destroy_shader_blob();

	public:
		ID3DBlob	*blob();
	};
}
