
#include "dir_light.h"


pulsar::dir_light::dir_light() : pulsar::light(pulsar::LIGHT_TYPE::DIR)
{

}

pulsar::dir_light::dir_light(const XMFLOAT3 &color) : pulsar::light(pulsar::LIGHT_TYPE::DIR)
{
	this->m_color = color;
}

XMFLOAT3	&pulsar::dir_light::color()
{
	return (this->m_color);
}
