#pragma once

#include "shader.h"


namespace pulsar
{
	class geom_shader : public pulsar::shader
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
		geom_shader(const LPCWSTR shader_file, const LPCSTR entry = pulsar::GEOM_ENTRY);
		~geom_shader();

		void	set(const LPCWSTR shader_file, const LPCSTR entry = pulsar::GEOM_ENTRY);
		const ID3D11GeometryShader	*get() const;

		void	bind() const;
		void	unbind() const;
	};
}
