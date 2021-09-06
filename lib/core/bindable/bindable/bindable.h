#pragma once

#include "pulsar_id3d.h"
#include "exc_macros.h"
#include "buffer_resource.h"
#include "piston.h"
#include "def_misc.h"
#include "bindable_manager.h"

#include <unordered_set>


namespace PULSAR
{
	enum class BINDABLE_TYPE
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


	enum class BIND_MODE
	{
		SRV,
		RTV
	};

	enum class BIND_SCOPE
	{
		LOCAL,
		GLOBAL
	};


	class BINDABLE_ENTITY;


	class BINDABLE : public PULSAR::PULSAR_ID3D
	{
	private:
		friend class ENTITY;			//	TODO: AVOID THIS

	private:
		static PULSAR::PISTON<PULSAR::BINDABLE*, PULSAR::MAX_BINDABLE_COUNT>			local_unbinds;
		static const PULSAR::IPISTON<PULSAR::BINDABLE*, PULSAR::MAX_BINDABLE_COUNT>		*local_iunbinds;

		static PULSAR::PISTON<PULSAR::BINDABLE*, PULSAR::MAX_BINDABLE_COUNT>			global_unbinds;
		static const PULSAR::IPISTON<PULSAR::BINDABLE*, PULSAR::MAX_BINDABLE_COUNT>		*global_iunbinds;

	protected:
		int		id = -1;
		bool	is_alloc = false;

		PULSAR::BINDABLE_TYPE			type = PULSAR::BINDABLE_TYPE::NONE;
		mutable PULSAR::BIND_SCOPE		scope = PULSAR::BIND_SCOPE::LOCAL;

		std::unordered_set<PULSAR::BINDABLE_ENTITY*>	entities;


		static BINDABLE		*add_to_manager(BINDABLE *bindable)
		{
			bindable->id = BM.add(bindable);
			if (bindable->id == -1)
			{
				delete bindable;
				return (NULL);
			}
			bindable->is_alloc = true;

			return (bindable);
		}

		static void		add_local_unbind(const BINDABLE &bindable)
		{
			BINDABLE::local_unbinds.add((BINDABLE*)&bindable);
		}
		static void		add_global_unbind(const BINDABLE &bindable)
		{
			BINDABLE::global_unbinds.add((BINDABLE*)&bindable);
		}
		static void		add_unbind(const BINDABLE &bindable)
		{
			switch (bindable.scope)
			{
				case BIND_SCOPE::LOCAL:
				{
					BINDABLE::add_local_unbind(bindable);
					break;
				}
				case BIND_SCOPE::GLOBAL:
				{
					BINDABLE::add_global_unbind(bindable);
					break;
				}
			}
		}

		virtual void	remove_from_entities() = 0;

	public:
		BINDABLE(){ }
		~BINDABLE()
		{
			this->destroy();
		}

		BINDABLE_TYPE	get_type() const
		{
			return (this->type);
		}
		int				get_id() const
		{
			return (this->id);
		}

		static void		unbind_local()
		{
			int i = -1;
			while (++i < BINDABLE::local_iunbinds->size)
				(*BINDABLE::local_iunbinds->data[i].data)->unbind();
			BINDABLE::local_unbinds.clear();
		}
		static void		unbind_global()
		{
			int i = -1;
			while (++i < BINDABLE::global_iunbinds->size)
				(*BINDABLE::global_iunbinds->data[i].data)->unbind();
			BINDABLE::global_unbinds.clear();
		}
		static void		unbind_all()
		{
			BINDABLE::unbind_local();
			BINDABLE::unbind_global();
		}

		void	add_to_entity(PULSAR::BINDABLE_ENTITY *entity)
		{
			this->entities.insert(entity);
		}
		void	remove_from_entity(PULSAR::BINDABLE_ENTITY *entity)
		{
			this->entities.erase(entity);
		}


		void	destroy()
		{
			if (!this->is_alloc)
				return;
			this->is_alloc = false;

			this->remove_from_entities();
			PULSAR::BM.remove_secure(this);
			delete this;
		}

		virtual void	bind() const = 0;
		void			bind(PULSAR::BIND_SCOPE scope) const
		{
			this->scope = scope;
			this->bind();
		}

		virtual void	unbind() const = 0;
	};
}
