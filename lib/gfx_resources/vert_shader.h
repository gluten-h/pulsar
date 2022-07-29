#pragma once

#include "shader.h"


namespace pulsar
{
	class vert_shader : public pulsar::shader
	{
	private:
		ID3D11VertexShader *mp_shader = NULL;

		void	create_vert_shader(const LPCWSTR shader_file, const LPCSTR entry);
		void	destroy_vert_shader();

	public:
		vert_shader &operator=(const vert_shader&) = delete;
		vert_shader &operator=(vert_shader&&) = delete;
		vert_shader(const vert_shader&) = delete;
		vert_shader(vert_shader&&) = delete;
		vert_shader() = default;
		vert_shader(const LPCWSTR shader_file, const LPCSTR entry = pulsar::VERT_ENTRY);
		~vert_shader();

		void	set(const LPCWSTR shader_file, const LPCSTR entry = pulsar::VERT_ENTRY);
		ID3D11VertexShader	*shader();

		void	bind() const;
		void	unbind() const;
	};
}
