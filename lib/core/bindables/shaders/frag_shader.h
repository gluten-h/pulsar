#pragma once

#include "shader.h"


namespace PULSAR
{
	class frag_shader : public PULSAR::shader
	{
	private:
		ID3D11PixelShader *mp_shader = NULL;

	private:
		void	free();
		void	create_shader(const LPCWSTR shader_file, const LPCSTR entry);

	public:
		frag_shader &operator=(const frag_shader&) = delete;
		frag_shader &operator=(frag_shader&&) = delete;
		frag_shader(const frag_shader&) = delete;
		frag_shader(frag_shader&&) = delete;
		frag_shader() = default;
		frag_shader(const LPCWSTR shader_file, const LPCSTR entry = PULSAR::FRAG_ENTRY);
		~frag_shader();

		void	set(const LPCWSTR shader_file, const LPCSTR entry = PULSAR::FRAG_ENTRY);
		const ID3D11PixelShader		*get() const;

		void	bind() const override;
		void	unbind() const override;
	};
}
