#pragma once

#include "grng_shader.h"
#include "grng_bindable_entity.h"


class grng_frag_shader : public GRNG_SHADER
{
private:
	ID3D11PixelShader			*shader = NULL;


	void						remove_frag_shader_memory();
	void						remove_shader_memory();
	void						set_shader_memory(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines);

	void						copy_assign(const grng_frag_shader &s);

protected:
	void		remove_from_entities() override
	{
		for (auto &it : this->entities)
			it->_remove_bindable_ignore_entity(this);
		this->entities.clear();
	}

public:
	using GRNG_BINDABLE::bind;

public:
	grng_frag_shader			&operator=(const grng_frag_shader &s);
	grng_frag_shader(const grng_frag_shader &s);
	grng_frag_shader();
	grng_frag_shader(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines);
	~grng_frag_shader();

	void		set(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines) override;

	const void	*get_shader() const
	{
		return ((void*)this->shader);
	}

	static grng_frag_shader		*create();

	void		bind() const override
	{
		this->device_context->PSSetShader(this->shader, NULL, 0u);
		GRNG_BINDABLE::add_unbind(*this);
	}

	void		unbind() const override
	{
		this->device_context->PSSetShader(NULL, NULL, 0u);
	}
};

using GRNG_FRAG_SHADER = grng_frag_shader;
