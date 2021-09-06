#pragma once

#include "shader.h"
#include "bindable_entity.h"


namespace PULSAR
{
	class FRAG_SHADER : public PULSAR::SHADER
	{
	private:
		ID3D11PixelShader	*shader = NULL;


		void	remove_frag_shader_memory();
		void	remove_shader_memory();
		void	set_shader_memory(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines);

		void	copy_assign(const FRAG_SHADER &s);

	protected:
		void	remove_from_entities() override
		{
			for (auto &it : this->entities)
				it->_remove_bindable_ignore_entity(this);
			this->entities.clear();
		}

	public:
		using PULSAR::BINDABLE::bind;

	public:
		FRAG_SHADER &operator=(const FRAG_SHADER &s);
		FRAG_SHADER(const FRAG_SHADER &s);
		FRAG_SHADER();
		FRAG_SHADER(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines);
		~FRAG_SHADER();

		void		set(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines) override;

		const void *get_shader() const
		{
			return ((void *)this->shader);
		}

		static FRAG_SHADER *create();

		void		bind() const override
		{
			this->device_context->PSSetShader(this->shader, NULL, 0u);
			BINDABLE::add_unbind(*this);
		}

		void		unbind() const override
		{
			this->device_context->PSSetShader(NULL, NULL, 0u);
		}
	};
}
