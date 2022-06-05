
#include "camera.h"


pulsar::camera::camera(UINT width, UINT height)
{
	this->m_viewport.set(width, height);
}

pulsar::viewport	&pulsar::camera::viewport()
{
	return (this->m_viewport);
}
