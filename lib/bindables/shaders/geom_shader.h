#pragma once

#include "shader.h"


namespace PULSAR
{
	class geom_shader : public PULSAR::shader
	{
	private:
		ID3D11GeometryShader *mp_shader = NULL;

	private:
		void	free();
		void	create_shader(const LPCWSTR shader_file, const LPCSTR entry);

	public:
		geom_shader &operator=(const geom_shader&) = delete;
		geom_shader &operator=(geom_shader&&) = delete;
		geom_shader(const geom_shader&) = delete;
		geom_shader(geom_shader&&) = delete;
		geom_shader() = default;
		geom_shader(const LPCWSTR shader_file, const LPCSTR entry = PULSAR::GEOM_ENTRY);
		~geom_shader();

		void	set(const LPCWSTR shader_file, const LPCSTR entry = PULSAR::GEOM_ENTRY);
		const ID3D11GeometryShader	*get() const;

		void	bind() const override;
		void	unbind() const override;
	};
}
