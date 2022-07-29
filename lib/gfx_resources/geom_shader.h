#pragma once

#include "shader.h"


namespace pulsar
{
	class geom_shader : public pulsar::shader
	{
	private:
		ID3D11GeometryShader *mp_shader = NULL;

		void	create_geom_shader(const LPCWSTR shader_file, const LPCSTR entry);
		void	destroy_geom_shader();

	public:
		geom_shader &operator=(const geom_shader&) = delete;
		geom_shader &operator=(geom_shader&&) = delete;
		geom_shader(const geom_shader&) = delete;
		geom_shader(geom_shader&&) = delete;
		geom_shader() = default;
		geom_shader(const LPCWSTR shader_file, const LPCSTR entry = pulsar::GEOM_ENTRY);
		~geom_shader();

		void	set(const LPCWSTR shader_file, const LPCSTR entry = pulsar::GEOM_ENTRY);
		ID3D11GeometryShader	*shader();

		void	bind() const;
		void	unbind() const;
	};
}
