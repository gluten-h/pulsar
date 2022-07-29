#pragma once

#include "shader.h"


namespace pulsar
{
	class frag_shader : public pulsar::shader
	{
	private:
		ID3D11PixelShader *mp_shader = NULL;

		void	create_frag_shader(const LPCWSTR shader_file, const LPCSTR entry);
		void	destroy_frag_shader();

	public:
		frag_shader &operator=(const frag_shader&) = delete;
		frag_shader &operator=(frag_shader&&) = delete;
		frag_shader(const frag_shader&) = delete;
		frag_shader(frag_shader&&) = delete;
		frag_shader() = default;
		frag_shader(const LPCWSTR shader_file, const LPCSTR entry = pulsar::FRAG_ENTRY);
		~frag_shader();

		void	set(const LPCWSTR shader_file, const LPCSTR entry = pulsar::FRAG_ENTRY);
		ID3D11PixelShader	*shader();

		void	bind() const;
		void	unbind() const;
	};
}
