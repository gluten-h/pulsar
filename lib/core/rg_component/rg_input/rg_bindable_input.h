//#pragma once
//
//#include "rg_input.h"
//#include "bindable.h"
//
//#include <type_traits>
//
//
//namespace PULSAR
//{
//	template<typename T>
//	class RG_BINDABLE_INPUT : public PULSAR::RG_INPUT
//	{
//	private:
//		static_assert(std::is_base_of_v<BINDABLE, T>, "RG_BINDABLE_INPUT target type must be a BINDABLE type");
//
//	private:
//		T	*source_bindable = NULL;
//
//	public:
//		RG_BINDABLE_INPUT(const std::string &name) : PULSAR::RG_INPUT(name){ }
//
//		static RG_BINDABLE_INPUT	*create(const std::string &name)
//		{
//			RG_BINDABLE_INPUT<T> *input = new RG_BINDABLE_INPUT<T>(name);
//			input->id = PULSAR::RGCM.add(input);
//			if (input->id == -1)
//			{
//				delete input;
//				return (NULL);
//			}
//			input->is_alloc = true;
//
//			return (input);
//		}
//
//		void		validate() const override
//		{
//			if (!this->source_buffer)
//				PULSAR::THROW_RG_EXC("RG_BINDABLE_INPUT " + this->get_name() + ": Unlinked input " + this->get_name());
//		}
//
//		void		bind(PULSAR::RG_SOURCE *source) override
//		{
//			T *source_bindable = dynamic_cast<T *>(source->yield_bindable());
//			if (!source_bindable)
//			{
//				PULSAR::THROW_RG_EXC("RG_BINDABLE_INPUT " + this->get_name() + ": Input " + this->get_name() + "of type " + typeid(T).name() + "is no compatible with "
//							 + this->get_source_pass_name() + "." + this->get_source_name() + " of type " + typeid(source->yield_buffer()).name());
//			}
//			this->source_bindable = source_bindable;
//		}
//	};
//}
