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
//	class RG_BUFFER_SOURCE : public PULSAR::RG_SOURCE
//	{
//	private:
//		static_assert(std::is_base_of_v<PULSAR::BUFFER_RESOURCE, T>, "RG_BUFFER_SOURCE target type must be a BUFFER_RESOURCE type");
//
//	private:
//		T		*buffer = NULL;
//		bool	linked = false;
//
//	public:
//		RG_BUFFER_SOURCE(const std::string &name, T *source_buffer) : PULSAR::RG_SOURCE(name)
//		{
//			this->buffer = source_buffer;
//		}
//
//		static RG_BUFFER_SOURCE		*create(const std::string &name, T *source_buffer)
//		{
//			RG_BUFFER_SOURCE<T> *source = new RG_BUFFER_SOURCE<T>(name, source_buffer);
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
//		PULSAR::BUFFER_RESOURCE		*yield_buffer() override
//		{
//			if (this->linked)
//				THROW_RG_EXC("RG_BUFFER_SOURCE " + this->get_name() + ": Source " + this->get_name() + " has already been linked");
//			this->linked = true;
//
//			return (this->buffer);
//		}
//	};
//}
