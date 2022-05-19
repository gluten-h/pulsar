#pragma once

#include "bindable/bindable.h"


namespace PULSAR
{
	class shader_texture : public PULSAR::bindable
	{
	private:
		ID3D11Texture2D *mp_texture = NULL;
		ID3D11ShaderResourceView *mp_srv = NULL;
		UINT m_slot = 0u;

	private:
		void	copy_assign(const shader_texture &st);
		void	create_shader_texture(const LPCWSTR file);
		void	free_texture();
		void	free_srv();
		void	free();

	public:
		shader_texture &operator=(const shader_texture &st);
		shader_texture &operator=(shader_texture&&) = delete;
		shader_texture(const shader_texture &st);
		shader_texture(shader_texture&&) = delete;
		shader_texture() = default;
		shader_texture(const LPCWSTR file, UINT slot = 0u);
		~shader_texture();

		void	set(const LPCWSTR file);
		void	set_slot(UINT slot);

		void	bind() const override;
		void	unbind() const override;
	};
}
