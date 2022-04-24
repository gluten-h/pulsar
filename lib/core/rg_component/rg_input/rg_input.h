#pragma once

#include "rg_component.h"
#include "exceptions/pulsar_exc.h"
#include "rg_source.h"

#include <string>


namespace PULSAR
{
	class RG_INPUT : public PULSAR::RG_COMPONENT
	{
	private:
		std::string		name;
		std::string		source_pass_name;
		std::string		source_name;


		void		copy_assign(const RG_INPUT &i)
		{
			this->name = i.name;
			this->source_pass_name = i.source_pass_name;
			this->source_name = i.source_name;
		}

	public:
		RG_INPUT	&operator=(const RG_INPUT &i)
		{
			this->copy_assign(i);

			return (*this);
		}
		RG_INPUT(const RG_INPUT &i) : PULSAR::RG_COMPONENT()
		{
			this->type = PULSAR::RG_COMPONENT_TYPE::INPUT;
			this->copy_assign(i);
		}
		RG_INPUT(const std::string &name) : PULSAR::RG_COMPONENT()
		{
			this->type = PULSAR::RG_COMPONENT_TYPE::INPUT;
			this->name = name;
		}

		const std::string	&get_name() const
		{
			return (this->name);
		}
		const std::string	&get_source_pass_name() const
		{
			return (this->source_pass_name);
		}
		const std::string	&get_source_name() const
		{
			return (this->source_name);
		}

		void		set_source(const std::string &source_pass_name, const std::string &source_name)
		{
			if (source_pass_name.empty())
				THROW_RG_EXC("RG_INPUT \"" + this->name + "\": Empty source name");
			this->source_pass_name = source_pass_name;

			if (source_name.empty())
				THROW_RG_EXC("RG_INPUT \"" + this->name + "\": Empty source name");
			this->source_name = source_name;
		}

		virtual void	validate() const{ }
		virtual void	bind(PULSAR::RG_SOURCE *source) = 0;
	};
}
