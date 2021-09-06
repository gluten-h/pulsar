//#pragma once
//
//#include "rg_source.h"
//#include "bindable.h"
//
//#include <type_traits>
//
//
//namespace PULSAR
//{
//	template<typename T>
//	class RG_BINDABLE_SOURCE : public RPULSAR::G_SOURCE
//	{
//	private:
//		static_assert(std::is_base_of_v<PULSAR::BINDABLE, T>, "RG_BINDABLE_SOURCE target type must be a BINDABLE type");
//
//	private:
//		T	*bindable = NULL;
//
//	public:
//		RG_BINDABLE_SOURCE(const std::string &name, T *source_bindable) : PULSAR::RG_SOURCE(name)
//		{
//			this->bindable = source_bindable;
//		}
//
//		static RG_BINDABLE_SOURCE		*create(const std::string &name, T *source_bindable)
//		{
//			RG_BINDABLE_SOURCE<T> *source = new RG_BINDABLE_SOURCE<T>(name, source_bindable);
//			source->id = PULSAR::RGCM.add(source);
//			if (source->id == -1)
//			{
//				delete source;
//				return (NULL);
//			}
//			source->is_alloc = true;
//
//			return (source);
//		}
//
//		PULSAR::BINDABLE	*yield_bindable() override
//		{
//			return (this->bindable);
//		}
//	};
//}
