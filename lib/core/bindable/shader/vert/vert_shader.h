#pragma once

#include "shader.h"
#include "bindable_entity.h"


namespace PULSAR
{
	class VERT_SHADER : public PULSAR::SHADER
	{
	private:
		ID3D11VertexShader		*shader = NULL;

		void	remove_vert_shader_memory();
		void	remove_shader_memory();
		void	set_shader_memory(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines);

		void	copy_assign(const VERT_SHADER &s);

	protected:
		void		remove_from_entities() override
		{
			for (auto &it : this->entities)
				it->_remove_bindable_ignore_entity(this);
			this->entities.clear();
		}

	public:
		using PULSAR::BINDABLE::bind;

	public:
		VERT_SHADER		&operator=(const VERT_SHADER &s);
		VERT_SHADER(const VERT_SHADER &s);
		VERT_SHADER();
		VERT_SHADER(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines);
		~VERT_SHADER();

		void	set(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines) override;

		const void		*get_shader() const
		{
			return ((void *)this->shader);
		}

		static VERT_SHADER		*create();

		void	bind() const override
		{
			this->device_context->VSSetShader(this->shader, NULL, 0u);
			BINDABLE::add_unbind(*this);
		}

		void	unbind() const override
		{
			this->device_context->VSSetShader(NULL, NULL, 0u);
		}
	};
}
