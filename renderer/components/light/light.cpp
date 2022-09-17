
#include "light.h"

pulsar::light::light(pulsar::LIGHT_TYPE type, pulsar::shadow_map *shadow_map)
{
	this->m_type = type;
	this->mp_shadow_map = shadow_map;
}

pulsar::LIGHT_TYPE	pulsar::light::type() const
{
	return (this->m_type);
}

pulsar::shadow_map	*pulsar::light::shadow_map()
{
	return (this->mp_shadow_map);
}
