#pragma once

#include "grng_bindables.h"
#include "grng_entities.h"
#include "grng_lights.h"
#include "grng_components.h"

#include <unordered_map>


#define GRNG_MP GRNG_MANAGER_PTR


typedef GRNG_BINDABLE *(*GRNG_MANAGER_PTR_BINDABLE)(void);
typedef GRNG_ENTITY *(*GRNG_MANAGER_PTR_ENTITY)(void);
typedef GRNG_LIGHT *(*GRNG_MANAGER_PTR_LIGHT)(void);
typedef GRNG_COMPONENT *(*GRNG_MANAGER_PTR_COMPONENT)(void);


class grng_manager_ptr
{
private:
	static std::unordered_map<GRNG_BINDABLE_TYPE, GRNG_MANAGER_PTR_BINDABLE>		bindable_ptr;
	static std::unordered_map<GRNG_ENTITY_TYPE, GRNG_MANAGER_PTR_ENTITY>			entity_ptr;
	static std::unordered_map<GRNG_LIGHT_TYPE, GRNG_MANAGER_PTR_LIGHT>				light_ptr;
	static std::unordered_map<GRNG_COMPONENT_TYPE, GRNG_MANAGER_PTR_COMPONENT>		component_ptr;

public:
	static void		create()
	{
		grng_manager_ptr::bindable_ptr[GRNG_BINDABLE_TYPE::VERT_CONST_BUFFER] = GRNG_VERT_CONST_BUFFER<int>::create_manager_ptr;
		grng_manager_ptr::bindable_ptr[GRNG_BINDABLE_TYPE::FRAG_CONST_BUFFER] = GRNG_FRAG_CONST_BUFFER<int>::create_manager_ptr;
		grng_manager_ptr::bindable_ptr[GRNG_BINDABLE_TYPE::TEXTURE] = GRNG_TEXTURE::create_manager_ptr;
		grng_manager_ptr::bindable_ptr[GRNG_BINDABLE_TYPE::DEPTH_STENCIL_VIEW] = GRNG_DEPTH_STENCIL_VIEW::create_manager_ptr;
		grng_manager_ptr::bindable_ptr[GRNG_BINDABLE_TYPE::DEPTH_STENCIL_STATE] = GRNG_DEPTH_STENCIL_STATE::create_manager_ptr;
		grng_manager_ptr::bindable_ptr[GRNG_BINDABLE_TYPE::INPUT_LAYOUT] = GRNG_INPUT_LAYOUT::create_manager_ptr;
		grng_manager_ptr::bindable_ptr[GRNG_BINDABLE_TYPE::RENDER_TEXTURE] = GRNG_RENDER_TEXTURE::create_manager_ptr;
		grng_manager_ptr::bindable_ptr[GRNG_BINDABLE_TYPE::VERT_SHADER] = GRNG_VERT_SHADER::create_ptr;
		grng_manager_ptr::bindable_ptr[GRNG_BINDABLE_TYPE::GEOM_SHADER] = GRNG_GEOM_SHADER::create_manager_ptr;
		grng_manager_ptr::bindable_ptr[GRNG_BINDABLE_TYPE::FRAG_SHADER] = GRNG_FRAG_SHADER::create_manager_ptr;
		grng_manager_ptr::bindable_ptr[GRNG_BINDABLE_TYPE::CUBEMAP] = GRNG_CUBEMAP::create_manager_ptr;
		grng_manager_ptr::bindable_ptr[GRNG_BINDABLE_TYPE::RASTERIZER_STATE] = GRNG_RASTERIZER_STATE::create_manager_ptr;

		grng_manager_ptr::entity_ptr[GRNG_ENTITY_TYPE::OBJECT] = GRNG_OBJECT::create_manager_ptr;

		grng_manager_ptr::light_ptr[GRNG_LIGHT_TYPE::POINT] = GRNG_POINT_LIGHT::create_manager_ptr;
		grng_manager_ptr::light_ptr[GRNG_LIGHT_TYPE::DIR] = GRNG_DIR_LIGHT::create_manager_ptr;

		grng_manager_ptr::component_ptr[GRNG_COMPONENT_TYPE::CAMERA] = GRNG_CAMERA::create_manager_ptr;
		grng_manager_ptr::component_ptr[GRNG_COMPONENT_TYPE::MATERIAL] = GRNG_MATERIAL::create_manager_ptr;
		grng_manager_ptr::component_ptr[GRNG_COMPONENT_TYPE::MESH] = GRNG_MESH::create_manager_ptr;
	}

	static void		destroy()
	{
		grng_manager_ptr::bindable_ptr.clear();
		grng_manager_ptr::entity_ptr.clear();
		grng_manager_ptr::light_ptr.clear();
	}


	static GRNG_BINDABLE	*create_ptr(const GRNG_BINDABLE_TYPE &type)
	{
		return (grng_manager_ptr::bindable_ptr.at(type)());
	}

	static GRNG_ENTITY		*create_ptr(const GRNG_ENTITY_TYPE &type)
	{
		return (grng_manager_ptr::entity_ptr.at(type)());
	}

	static GRNG_LIGHT		*create_ptr(const GRNG_LIGHT_TYPE &type)
	{
		return (grng_manager_ptr::light_ptr.at(type)());
	}

	static GRNG_COMPONENT	*create_ptr(const GRNG_COMPONENT_TYPE &type)
	{
		return (grng_manager_ptr::component_ptr.at(type)());
	}
};

using GRNG_MANAGER_PTR = grng_manager_ptr;
