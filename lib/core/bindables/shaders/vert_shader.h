#pragma once

#include "shader.h"


namespace PULSAR
{
	class vert_shader : public PULSAR::shader
	{
	private:
		ID3D11VertexShader *mp_shader = NULL;

	private:
		void	free();
		void	create_shader(const LPCWSTR shader_file, const LPCSTR entry);

	public:
		vert_shader &operator=(const vert_shader&) = delete;
		vert_shader &operator=(vert_shader&&) = delete;
		vert_shader(const vert_shader&) = delete;
		vert_shader(vert_shader&&) = delete;
		vert_shader() = default;
		vert_shader(const LPCWSTR shader_file, const LPCSTR entry = PULSAR::VERT_ENTRY);
		~vert_shader();

		void	set(const LPCWSTR shader_file, const LPCSTR entry = PULSAR::VERT_ENTRY);
		const ID3D11VertexShader	*get() const;

		void	bind() const override;
		void	unbind() const override;
	};
}
