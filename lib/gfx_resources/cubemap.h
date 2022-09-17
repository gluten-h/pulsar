#pragma once

#include "shader_texture.h"


namespace pulsar
{
	enum class FILE_CREATION
	{
		OVERWRITE,
		KEEP_IF_EXISTS
	};

	class cubemap : protected pulsar::shader_texture
	{
	private:
		void	copy_assign(const cubemap &c);
		void	create_srv(LPCWSTR dds_file);
		void	destroy_srv();
		void	convert_to_dds(LPCWSTR *files, LPCWSTR output_dds_path);

	public:
		cubemap &operator=(const cubemap &c);
		cubemap &operator=(cubemap&&) = delete;
		cubemap(const cubemap &c);
		cubemap(cubemap&&) = delete;
		cubemap() = default;
		cubemap(LPCWSTR *files, LPCWSTR output_dds_path, FILE_CREATION behavior = FILE_CREATION::OVERWRITE, UINT slot = 0u);
		cubemap(LPCWSTR dds_file, UINT slot = 0u);
		~cubemap();

		//Face order: pos_x, neg_x, pos_y, neg_y, pos_z, neg_z
		void	set(LPCWSTR *files, LPCWSTR output_dds_path, FILE_CREATION behavior = FILE_CREATION::OVERWRITE);
		void	set(LPCWSTR dds_file);
		void	set_slot(UINT slot);

		void	bind() const;
		void	unbind() const;
	};
}
