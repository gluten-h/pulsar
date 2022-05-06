#pragma once

#include "bindable/bindable.h"


namespace PULSAR
{
	enum class CUBEMAP_DDS
	{
		OVERWRITE,
		KEEP_IF_EXISTS
	};

	class cubemap : PULSAR::bindable
	{
	private:
		ID3D11Texture2D *mp_texture2d = NULL;
		ID3D11ShaderResourceView *mp_srv = NULL;
		UINT m_slot = 0u;

	private:
		void	free();
		void	create_cubemap(LPCWSTR dds_path);
		void	save_dds_cubemap(LPCWSTR *wic_path, LPCWSTR output_dds_path);

	public:
		cubemap	&operator=(const cubemap&) = delete;
		cubemap &operator=(cubemap&&) = delete;
		cubemap(const cubemap&) = delete;
		cubemap(cubemap&&) = delete;
		cubemap() = default;
		cubemap(LPCWSTR *wic_path, LPCWSTR output_dds_path, CUBEMAP_DDS dds_behavior = CUBEMAP_DDS::OVERWRITE, UINT slot = 0u);
		cubemap(LPCWSTR dds_path, UINT slot = 0u);
		~cubemap();

		void	set(LPCWSTR *wic_path, LPCWSTR output_dds_path, CUBEMAP_DDS dds_behavior = CUBEMAP_DDS::OVERWRITE);
		void	set(LPCWSTR dds_path);
		void	set_slot(UINT slot);

		void	bind() const override;
		void	unbind() const override;
	};
}
