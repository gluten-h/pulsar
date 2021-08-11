#pragma once

#include "grng_id3d.h"
#include "grng_exc_macros.h"
#include "grng_buffer_resource.h"
#include "grng_piston.h"
#include "grng_def_misc.h"
#include "grng_bindable_manager.h"

#include <unordered_set>


enum class GRNG_BINDABLE_TYPE
{
	NONE,
	VERT_CONST_BUFFER,
	FRAG_CONST_BUFFER,
	TEXTURE,
	DEPTH_STENCIL_VIEW,
	DEPTH_STENCIL_STATE,
	INPUT_LAYOUT,
	RENDER_TEXTURE,
	SAMPLER,
	VERT_SHADER,
	GEOM_SHADER,
	FRAG_SHADER,
	CUBEMAP,
	RASTERIZER_STATE,
	RENDER_TARGET,
	VIEWPORT,
	MESH
};


enum class GRNG_BIND_MODE
{
	SRV,
	RTV
};

enum class GRNG_BIND_SCOPE
{
	LOCAL,
	GLOBAL
};


class grng_bindable_entity;


class grng_bindable : public GRNG_ID3D
{
private:
	friend class grng_entity;			//	TODO: AVOID THIS

private:
	static GRNG_PISTON<grng_bindable*, GRNG_MAX_BINDABLE_COUNT>				local_unbinds;
	static const GRNG_IPISTON<grng_bindable*, GRNG_MAX_BINDABLE_COUNT>		*local_iunbinds;

	static GRNG_PISTON<grng_bindable*, GRNG_MAX_BINDABLE_COUNT>				global_unbinds;
	static const GRNG_IPISTON<grng_bindable*, GRNG_MAX_BINDABLE_COUNT>		*global_iunbinds;

protected:
	int			id = -1;
	bool		is_alloc = false;

	GRNG_BINDABLE_TYPE			type = GRNG_BINDABLE_TYPE::NONE;
	mutable GRNG_BIND_SCOPE		scope = GRNG_BIND_SCOPE::LOCAL;

	std::unordered_set<grng_bindable_entity*>	entities;


	static void		add_local_unbind(const grng_bindable &bindable)
	{
		grng_bindable::local_unbinds.add((grng_bindable*)&bindable);
	}
	static void		add_global_unbind(const grng_bindable &bindable)
	{
		grng_bindable::global_unbinds.add((grng_bindable*)&bindable);
	}
	static void		add_unbind(const grng_bindable &bindable)
	{
		switch (bindable.scope)
		{
			case GRNG_BIND_SCOPE::LOCAL:
			{
				grng_bindable::add_local_unbind(bindable);
				break;
			}
			case GRNG_BIND_SCOPE::GLOBAL:
			{
				grng_bindable::add_global_unbind(bindable);
				break;
			}
		}
	}

	virtual void	remove_from_entities() = 0;

public:
	grng_bindable() : GRNG_ID3D(){ }
	~grng_bindable()
	{
		this->destroy();
	}

	GRNG_BINDABLE_TYPE		get_type() const
	{
		return (this->type);
	}
	int						get_id() const
	{
		return (this->id);
	}

	static void		unbind_local()
	{
		int i = -1;
		while (++i < grng_bindable::local_iunbinds->size)
			(*grng_bindable::local_iunbinds->data[i].data)->unbind();
		grng_bindable::local_unbinds.clear();
	}
	static void		unbind_global()
	{
		int i = -1;
		while (++i < grng_bindable::global_iunbinds->size)
			(*grng_bindable::global_iunbinds->data[i].data)->unbind();
		grng_bindable::global_unbinds.clear();
	}
	static void		unbind_all()
	{
		grng_bindable::unbind_local();
		grng_bindable::unbind_global();
	}

	void	add_to_entity(grng_bindable_entity *entity)
	{
		this->entities.insert(entity);
	}
	void	remove_from_entity(grng_bindable_entity *entity)
	{
		this->entities.erase(entity);
	}


	void	destroy()
	{
		if (!this->is_alloc)
			return;
		this->is_alloc = false;

		this->remove_from_entities();
		GRNG_BM.remove_secure(this);
		delete this;
	}

	virtual void	bind() const = 0;
	void			bind(GRNG_BIND_SCOPE scope) const
	{
		this->scope = scope;
		this->bind();
	}

	virtual void	unbind() const = 0;
};

using GRNG_BINDABLE = grng_bindable;
