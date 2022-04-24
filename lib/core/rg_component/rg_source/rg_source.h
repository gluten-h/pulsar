#pragma once

#include "exceptions/pulsar_exc.h"
#include "rg_component.h"
#include "buffer_resource.h"

#include <string>


namespace PULSAR
{
	class RG_SOURCE : public PULSAR::RG_COMPONENT
	{
	private:
		std::string		name;


		void		copy_assign(const RG_SOURCE &s)
		{
			this->name = s.name;
		}

	public:
		RG_SOURCE	&operator=(const RG_SOURCE &o)
		{
			this->copy_assign(o);

			return (*this);
		}
		RG_SOURCE(const RG_SOURCE &s)
		{
			this->type = PULSAR::RG_COMPONENT_TYPE::SOURCE;
			this->copy_assign(s);
		}
		RG_SOURCE(const std::string &name)
		{
			this->type = PULSAR::RG_COMPONENT_TYPE::SOURCE;
			this->name = name;
		}

		const std::string	&get_name() const
		{
			return (this->name);
		}


		virtual void		validate() const{ }


		virtual PULSAR::BUFFER_RESOURCE		**yield_buffer()
		{
			THROW_RG_EXC("RG_SOURCE \"" + this->name + "\": cannot be accessed as buffer");
		}

		virtual PULSAR::BINDABLE	**yield_bindable()
		{
			THROW_RG_EXC("RG_SOURCE \"" + this->name + "\": cannot be accessed as bindable");
		}
	};
}
