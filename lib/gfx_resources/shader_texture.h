#pragma once

#include "texture2d_resource.h"


namespace pulsar
{
	class shader_texture : public pulsar::texture2d_resource
	{
	protected:
		ID3D11ShaderResourceView *mp_srv = NULL;
		UINT m_slot = 0u;

	private:
		void	copy_assign(const shader_texture &st);
		void	create_srv(const LPCWSTR file);
		void	destroy_srv();

	public:
		shader_texture &operator=(const shader_texture &st);
		shader_texture &operator=(shader_texture&&) = delete;
		shader_texture(const shader_texture &st);
		shader_texture(shader_texture&&) = delete;
		shader_texture() = default;
		shader_texture(const LPCWSTR file, UINT slot = 0u);
		virtual ~shader_texture();

		void	set(const LPCWSTR file);
		void	set_slot(UINT slot);

		void	bind() const;
		void	unbind() const;
	};

	using srv = pulsar::shader_texture;
}
