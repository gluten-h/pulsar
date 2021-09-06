#pragma once

#include "shader.h"
#include "bindable_entity.h"


namespace PULSAR
{
	class GEOM_SHADER : public PULSAR::SHADER
	{
	private:
		ID3D11GeometryShader	*shader = NULL;


		void	remove_geom_shader_memory();
		void	remove_shader_memory();
		void	set_shader_memory(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines);

		void	copy_assign(const GEOM_SHADER &s);

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
		GEOM_SHADER &operator=(const GEOM_SHADER &s);
		GEOM_SHADER(const GEOM_SHADER &s);
		GEOM_SHADER();
		GEOM_SHADER(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines);
		~GEOM_SHADER();

		void	set(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines) override;

		const void *get_shader() const
		{
			return ((void *)this->shader);
		}

		static GEOM_SHADER		*create();

		void	bind() const override
		{
			this->device_context->GSSetShader(this->shader, NULL, 0u);
			BINDABLE::add_unbind(*this);
		}

		void	unbind() const override
		{
			this->device_context->GSSetShader(NULL, NULL, 0u);
		}
	};
}
