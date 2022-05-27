
#include "light.h"

pulsar::light::light(pulsar::LIGHT_TYPE type)
{
	this->m_type = type;
}

pulsar::LIGHT_TYPE	pulsar::light::type() const
{
	return (this->m_type);
}
