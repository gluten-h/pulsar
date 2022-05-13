//#pragma once
//
//#include "unclassified.h"
//#include "exceptions/pulsar_exc.h"
//#include "component_manager.h"
//
//
//namespace PULSAR
//{
//	enum class COMPONENT_TYPE
//	{
//		NONE,
//		CAMERA,
//		MATERIAL,
//		SKYBOX_MATERIAL,
//	};
//
//
//	class COMPONENT : public PULSAR::unclassified
//	{
//	protected:
//		int		id = -1;
//		bool	is_alloc = false;
//		COMPONENT_TYPE		type = COMPONENT_TYPE::NONE;
//
//
//		static COMPONENT	*add_to_manager(COMPONENT *component)
//		{
//			component->id = PULSAR::COMPONENT_MANAGER::get_instance().add(component);
//			if (component->id == -1)
//			{
//				delete component;
//				return (NULL);
//			}
//			component->is_alloc = true;
//
//			return (component);
//		}
//
//	public:
//		COMPONENT(){ }
//		~COMPONENT()
//		{
//			this->destroy();
//		}
//
//		void	destroy()
//		{
//			if (!this->is_alloc)
//				return;
//			this->is_alloc = false;
//
//			PULSAR::COMPONENT_MANAGER::get_instance().remove(this);
//			delete this;
//		}
//
//		COMPONENT_TYPE		get_type() const
//		{
//			return (this->type);
//		}
//		int		get_id() const
//		{
//			return (this->id);
//		}
//	};
//}
